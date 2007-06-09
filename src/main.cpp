#include <QApplication>

#include "mainwindow.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

/*   	if (lang != "English") {
		QTranslator * translator = new QTranslator;
		translator->load(QString(":/i18n/%1.qm").arg(lang));
		app.installTranslator(translator);
	}*/
	/*         QTranslator qtTranslator;
         qtTranslator.load("qt_" + QLocale::system().name());
         app.installTranslator(&qtTranslator);

         QTranslator myappTranslator;
         myappTranslator.load("myapp_" + QLocale::system().name());
         app.installTranslator(&myappTranslator);*/

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
