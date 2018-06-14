#include <QApplication>
#include "mainmanager.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainManager * mainmanager = new MainManager();

    mainmanager->show_login();

    return a.exec();
}
