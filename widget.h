#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
     void setLabelStatusText(QString text);

private:
    Ui::Widget *ui;
    void setStartUI();
    void connectsInit();       // init all connects


private slots:
    void login_to_server();


signals:
    void run_login(QString login, QString password);


};

#endif // WIDGET_H
