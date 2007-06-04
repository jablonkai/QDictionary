#include "mainwindow.h"

#include <QtGui>

#include "dictionary.h"
#include "dictionarywidget.h"
#include "version.h"


MainWindow::MainWindow() : QMainWindow()
{
	ui.setupUi(this);
	setupActions();
	
	centralWidget = new QStackedWidget;
	setCentralWidget(centralWidget);
	
	dictionaryWidget = new DictionaryWidget;
	centralWidget->addWidget(dictionaryWidget);
	
	readSettings();
	
	connect(ui.treeWidget, SIGNAL(activateDictionary(Dictionary*)), dictionaryWidget, SLOT(activateDictionary(Dictionary*)));
	connect(ui.treeWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
	connect(dictionaryWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
}


void MainWindow::closeEvent(QCloseEvent *event)
{
	writeSettings();
    event->accept();
}


void MainWindow::slotAbout()
{
	QMessageBox::about(this, tr("About QDictionary"), QString::fromUtf8("QDictionary\nVersion " QDICT_VERSION_STRING "\nCopyright (C) 2007 by Tamás Jablonkai\ntamas.jablonkai@gmail.com"));
}


void MainWindow::setupActions()
{
	connect(ui.actionQuit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));
	connect(ui.actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}


void MainWindow::readSettings()
{
    QSettings settings("Jablonkai", "QDictionary");

    settings.beginGroup("MainWindow");
    restoreState(settings.value("state", saveState()).toByteArray());
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    settings.endGroup();
}


void MainWindow::writeSettings()
{
    QSettings settings("Jablonkai", "QDictionary");

    settings.beginGroup("MainWindow");
    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();
}
