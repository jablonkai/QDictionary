#include "mainwindow.h"

#include <QtGui>

#include "aboutdialog.h"
#include "dictionary.h"
#include "dictionarywidget.h"
#include "newdialog.h"
#include "version.h"


MainWindow::MainWindow() : QMainWindow()
{
    ui.setupUi(this);
    setupActions();

    readSettings();

    connect(ui.treeWidget, SIGNAL(activateDictionary(Dictionary*)), ui.dictionaryWidget, SLOT(activateDictionary(Dictionary*)));
    connect(ui.treeWidget, SIGNAL(activateDictionary(Dictionary*)), ui.editWidget, SLOT(activateDictionary(Dictionary*)));
    connect(ui.treeWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
    connect(ui.dictionaryWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
    connect(ui.editWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}


void MainWindow::slotNew()
{
    Dictionary *dict = new Dictionary;
    NewDialog *dialog = new NewDialog(this, dict);

    if (dialog->exec() == QDialog::Accepted)
    {
        ui.treeWidget->addNewDictionary(dict);
        ui.stackedWidget->setCurrentWidget(ui.editWidget);
    }
    else
        delete dict;
}


void MainWindow::slotSetMode(QAction *action)
{
    if (action == ui.actionDictionary)
        ui.stackedWidget->setCurrentWidget(ui.dictionaryWidget);
    else if (action == ui.actionEdit)
        ui.stackedWidget->setCurrentWidget(ui.editWidget);
}


void MainWindow::slotAbout()
{
    AboutDialog *dialog = new AboutDialog(this);
    dialog->exec();
//    QMessageBox::about(this, tr("About QDictionary"), QString::fromUtf8("QDictionary\nVersion " QDICT_VERSION_STRING "\nCopyright (C) 2007 by Tamás Jablonkai\ntamas.jablonkai@gmail.com"));
}


void MainWindow::setupActions()
{
    connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(slotNew()));
    connect(ui.actionQuit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    QActionGroup *modeGroup = new QActionGroup(this);
    modeGroup->addAction(ui.actionDictionary);
    modeGroup->addAction(ui.actionEdit);
    connect(modeGroup, SIGNAL(triggered(QAction*)), this, SLOT(slotSetMode(QAction*)));

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
