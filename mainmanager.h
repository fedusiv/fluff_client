#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include <QObject>
#include "widget.h"
#include "client.h"

class MainManager : public QObject
{
    Q_OBJECT
public:
    explicit MainManager(QObject *parent = nullptr);
    void show_login();

signals:

public slots:


private:
    Widget * widget_login;
    Client * client;
    void connectsInit();    // init connects in this class


private slots:
    void connectToServer(QString login, QString password);          // to connect to sever
    void connectedSocket();                                         // socket connected to server
};

#endif // MAINMANAGER_H
