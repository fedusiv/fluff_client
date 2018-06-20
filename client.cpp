#include "client.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    timer_connect_to_host = new QTimer();

    fill_commands_dict();
    connectsInit();

    socket->connectToHost("localhost",9999);                            // connect to server
    timer_connect_to_host->start(const_timer_connect_to_host_time);     // start timer for connection
}

void Client::connectToServer(QString login, QString password)
{
    login_ = login;
    password_ = password;
    logging_in();

}

void Client::connectsInit()
{
    connect(socket,SIGNAL(connected()),this,SLOT(socketConnected()));       // spcket connected with tcp socket
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(errorSocketOccur(QAbstractSocket::SocketError)));      // when error
    connect(socket,SIGNAL(readyRead()),this,SLOT(readFromSocket()));        // get read data
    connect(timer_connect_to_host,SIGNAL(timeout()),this,SLOT(onTimerConnectionToHost()));                                      // timer connection timeot
}

//logging to server system
void Client::logging_in()
{
    QJsonObject log_command{
        {"command","login"},
        {"login", login_},
        {"password", password_}
    };
    qDebug()<<log_command;
    QJsonDocument jdoc(log_command);
    socket->write(jdoc.toJson());


}

void Client::fill_commands_dict()
{
    commands_dict["login"] =    commands_login_parse;
    commands_dict["password"] = commands_register_parse;
}

// parse commands with login
void Client::commands_login_parse(QJsonObject *j_obj)
{
    QString result_ = j_obj->value("result").toString();
    if(result_ == "correct"){
       emit loggedSuccessful();     // when login ok
    }else{
                                    // when login not ok
        qDebug()<<"incorrect";
    }
}

void Client::commands_register_parse(QJsonObject *j_obj)
{

}

// read from socket
void Client::readFromSocket()
{
    QByteArray msg_ = socket->readAll();                    // read
    QJsonDocument j_msg = QJsonDocument::fromJson(msg_);    // convert
    QJsonObject j_obj = j_msg.object();                     // convert to json obj
    QString command = j_obj.value("command").toString();    // get command of msg

    (this->*commands_dict.value(command))(&j_obj);                // run function for parsing
}

void Client::errorSocketOccur(QAbstractSocket::SocketError e)
{
    Q_UNUSED(e);
    emit errorOccur(socket->errorString());

}

void Client::onTimerConnectionToHost()
{
    static int dot_counter = 0;
    QString con_str = "connecting";
    if(socket->state() != QAbstractSocket::ConnectedState ){
        if(socket->state() == QAbstractSocket::UnconnectedState)
            socket->connectToHost("localhost",9999);           // connect to server
        QString dot_str="";
        for(int i=0;i<dot_counter;i++){
            con_str+=". ";
        }
        if(++dot_counter > 4){
            dot_counter = 0;
        }
        emit connection_status_ui_label_update(con_str);
    }

}

void Client::socketConnected()
{
    emit socketHasConnect();
}
