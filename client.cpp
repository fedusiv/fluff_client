#include "client.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    connectsInit();
}

Client::connectToServer(QString login, QString password)
{
    login_ = login;
    password_ = password;
    socket->connectToHost("localhost",9999);
}

void Client::connectsInit()
{
    connect(socket,SIGNAL(connected()),this,SLOT(socketConnected()));
}

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

void Client::socketConnected()
{
    emit socketHasConnect();
    logging_in();

}
