#include "mainmanager.h"
#include <QDebug>

MainManager::MainManager(QObject *parent) : QObject(parent)
{
    widget_login = new Widget();
    client       = new Client();
    connectsInit();
}

void MainManager::show_login()
{
    widget_login->show();
}

void MainManager::connectsInit()
{
    connect(widget_login,SIGNAL(run_login(QString,QString)),this,SLOT(connectToServer(QString,QString)));
    connect(client,SIGNAL(socketHasConnect()),this,SLOT(connectedSocket()));
}

void MainManager::connectToServer(QString login, QString password)
{
    client->connectToServer(login,password);
}

void MainManager::connectedSocket()
{
    widget_login->setLabelStatusText("connected");
}
