#include "client.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    fill_commands_dict();
    connectsInit();
    socket->connectToHost("localhost",9999);
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

void Client::socketConnected()
{
    emit socketHasConnect();
}
