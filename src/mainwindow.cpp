/***************************************************************************
 *   Copyright (C) 2007 by Jablonkai Tamás                                 *
 *   tamas.jablonkai@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "mainwindow.h"

#include <QtGui>

#include "dictionary.h"
#include "dictionarywidget.h"
//#include "newdialog.h"
#include "settings.h"
#include "settingsdialog.h"
#include "version.h"


MainWindow::MainWindow() : QMainWindow()
{
    ui.setupUi(this);
    setupActions();

    _settings = new Settings;
    readSettings();
    ui.treeWidget->initDicts(_settings->dictDirs());

    connect(ui.treeWidget, SIGNAL(activateDictionary(Dictionary*)), ui.dictionaryWidget, SLOT(activateDictionary(Dictionary*)));
//    connect(ui.treeWidget, SIGNAL(activateDictionary(Dictionary*)), ui.editWidget, SLOT(activateDictionary(Dictionary*)));
    connect(ui.treeWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
    connect(ui.dictionaryWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
//    connect(ui.editWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));

    ui.dictionaryWidget->init(_settings);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}


void MainWindow::slotNew()
{
/*    DictionaryModel *dict = new DictionaryModel;
    NewDialog *dialog = new NewDialog(this, dict);

    if (dialog->exec() == QDialog::Accepted)
    {
        ui.treeWidget->addNewDictionary(dict);
        ui.stackedWidget->setCurrentWidget(ui.editWidget);
    }
    else
        delete dict;*/
}


void MainWindow::slotSave()
{
}


void MainWindow::slotSettings()
{
    SettingsDialog *dialog = new SettingsDialog(_settings, this);

    if (dialog->exec() == QDialog::Accepted)
        ui.treeWidget->initDicts(_settings->dictDirs());
}


void MainWindow::slotAbout()
{
    QMessageBox::about(this, tr("About QDictionary"), QString::fromUtf8("QDictionary\nVersion " QDICTIONARY_VERSION_STRING "\nCopyright (C) 2007 by Tamás Jablonkai\ntamas.jablonkai@gmail.com"));
}


void MainWindow::setupActions()
{
//    connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(slotNew()));
//    connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(slotSave()));
    connect(ui.actionQuit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    connect(ui.actionSettings, SIGNAL(triggered()), this, SLOT(slotSettings()));
    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));
    connect(ui.actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}


void MainWindow::readSettings()
{
    QSettings settings;

    settings.beginGroup("MainWindow");
    restoreState(settings.value("state", saveState()).toByteArray());
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    settings.endGroup();

    settings.beginGroup("Dictionary");
    _settings->setDictDirs(settings.value("dirs", _settings->dictDirs()).toStringList());
    _settings->setFirstColor(settings.value("firstColor", _settings->firstColor()).value<QColor>());
    _settings->setSecondColor(settings.value("secondColor", _settings->secondColor()).value<QColor>());
    settings.endGroup();
}


void MainWindow::writeSettings()
{
    QSettings settings;

    settings.beginGroup("MainWindow");
    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();

    settings.beginGroup("Dictionary");
    settings.setValue("dirs", _settings->dictDirs());
    settings.setValue("firstColor", _settings->firstColor());
    settings.setValue("secondColor", _settings->secondColor());
    settings.endGroup();
}
