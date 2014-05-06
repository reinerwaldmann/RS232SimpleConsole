
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //PrincipalWindow w;
    //w.show();
    

    MainWindow mw ; //тестовый интерфейс для Device manager
    mw.show();

    return a.exec();
}
