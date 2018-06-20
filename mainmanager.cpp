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
    connect(client,SIGNAL(connection_status_ui_label_update(QString)),widget_login,SLOT(setLabelStatusConnectionText(QString))); // ui part
}

void MainManager::connectToServer(QString login, QString password)
{
    client->connectToServer(login,password);
}

void MainManager::connectedSocket()
{
    widget_login->setLabelStatusText("connected");
    widget_login->setLabelStatusConnectionText("");
}

void MainManager::loggedClient()
{
    widget_login->setLabelStatusText("LOGGED");
}

void MainManager::errorOccur(QString e_string)
{
    widget_login->setLabelStatusText(e_string);
}
