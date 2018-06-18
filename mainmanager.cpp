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
    connect(client,SIGNAL(loggedSuccessful()),this,SLOT(loggedClient()));
    connect(client,SIGNAL(errorOccur(QString)),this,SLOT(errorOccur(QString)));                             // error occur error msg
}

void MainManager::connectToServer(QString login, QString password)
{
    client->connectToServer(login,password);
}

void MainManager::connectedSocket()
{
    widget_login->setLabelStatusText("connected");
}

void MainManager::loggedClient()
{
    widget_login->setLabelStatusText("LOGGED");
}

void MainManager::errorOccur(QString e_string)
{
    widget_login->setLabelStatusText(e_string);
}
