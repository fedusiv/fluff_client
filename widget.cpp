#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setStartUI();
    connectsInit();

}



Widget::~Widget()
{
    delete ui;
}

void Widget::setStartUI()
{
    ui->lineEdit_login->setPlaceholderText("login");
    ui->lineEdit_password->setPlaceholderText("password");
}

void Widget::connectsInit()
{
    connect(ui->pushButton_LogIn,SIGNAL(clicked(bool)),this,SLOT(login_to_server()));   // pushbutton for connect to server
}

void Widget::setLabelStatusText(QString text)
{
    ui->label_Status->setText(text);
}

void Widget::setLabelStatusConnectionText(QString text)
{
    ui->label_StatusConnection->setText(text);
}

void Widget::login_to_server()
{
    // check input parametrs
    if(ui->lineEdit_login->text().isEmpty()){
        QMessageBox::warning(this, "Warning!","Incorrect login input");
        return;
    }
    if(ui->lineEdit_password->text().isEmpty()){
        QMessageBox::warning(this, "Warning!","Incorrect password input");
        return;
    }
    // go to connect
    emit run_login(ui->lineEdit_login->text(),ui->lineEdit_password->text());
}
