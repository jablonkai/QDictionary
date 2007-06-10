#include <QApplication>
#include <QTranslator>

#include "mainwindow.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QTranslator myappTranslator;
    myappTranslator.load("qdictionary_" + QLocale::system().name(), qApp->applicationDirPath() + "/i18n");
    app.installTranslator(&myappTranslator);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
