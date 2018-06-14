#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    connectToServer(QString login, QString password);   // connect to server

signals:
    void socketHasConnect();                            // to show out the connect was made

public slots:


private:
    QTcpSocket * socket;
    void connectsInit();
    QString login_, password_;
    void logging_in();

private slots:
    void socketConnected();

};

#endif // CLIENT_H
