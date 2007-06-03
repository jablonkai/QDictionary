#include <QApplication>
#include <QTranslator>

#include "mainwindow.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name());
    app.installTranslator(&qtTranslator);
    
    QTranslator translator;
    translator.load("qdictionary_" + QLocale::system().name(), "i18n");
    app.installTranslator(&translator);
    
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
