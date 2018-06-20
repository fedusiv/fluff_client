#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMap>
#include <QJsonObject>
#include <QTimer>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer(QString login, QString password);   // connect to server

signals:
    void socketHasConnect();                            // to show out the connect was made
    void loggedSuccessful();                            // when succesfully connected
    void errorOccur(QString e_string);                  // error occur
    void connection_status_ui_label_update(QString string); // for update gui

public slots:


private:
    QTcpSocket * socket;
    QTimer * timer_connect_to_host;
    void connectsInit();
    QString login_, password_;                          // store login and pass
    void logging_in();                                  // func for log in
    QMap<QString,void (Client::*)(QJsonObject*)> commands_dict;     // dictionary for commands parsing
    void fill_commands_dict();                          // fill commands dictionary with elements
    const int const_timer_connect_to_host_time = 1000;  // time in ms for update connection. reconect e.t.c

    // zone of parsing functions
    void commands_login_parse(QJsonObject* j_obj);
    void commands_register_parse(QJsonObject* j_obj);

private slots:
    void socketConnected();                             // when we got tcp connection with server
    void readFromSocket();                              // read data from socket
    void errorSocketOccur(QAbstractSocket::SocketError e);
    void onTimerConnectionToHost();                     // callback for timer_connect_to_host

};

#endif // CLIENT_H
