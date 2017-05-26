#include <QApplication>
#include <QSplashScreen>
#include "mainwindow.h"
#include <QTranslator>
#include <QTime>
#include <QPixmap>


int main(int argc, char *argv[])
{  
    QApplication app(argc, argv);


    QTranslator translator;
    translator.load(":/qm/spreadsheet.qm");
    app.installTranslator(&translator);

    MainWindow mainWin;
    QSplashScreen *splash=new QSplashScreen;
    QPixmap pix(":/images/logo.png");

    splash->setPixmap(pix);
    splash->show();
    app.processEvents();

    splash->finish(&mainWin);
    mainWin.show();

    return app.exec();
}
