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
#include "popupwidget.h"
#include "settings.h"
#include "settingsdialog.h"


MainWindow::MainWindow() : QMainWindow()
{
    ui.setupUi(this);

    _settings = new Settings;

    createTrayIcon();
    popupWidget = new PopupWidget(this);
    createConnections();

    readSettings();
}


MainWindow::~MainWindow()
{
    writeSettings();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
    else
        event->accept();
}


void MainWindow::slotShowTrayIcon(bool b)
{
    if (b && ui.actionScan->isChecked())
        popupWidget->slotScan(b);
    else if (!b)
        popupWidget->slotScan(b);
}


void MainWindow::slotSettings()
{
    SettingsDialog *dialog = new SettingsDialog(_settings, this);

    if (dialog->exec() == QDialog::Accepted)
    {
        ui.treeWidget->initDicts(_settings->dictDirs());
        trayIcon->setVisible(_settings->showTrayIcon());
    }
}


void MainWindow::slotAbout()
{
    QMessageBox::about(this, tr("About QDictionary"), QString::fromUtf8("QDictionary\nVersion " QDICTIONARY_VERSION "\nCopyright (C) 2007 by Tamás Jablonkai\ntamas.jablonkai@gmail.com"));
}


void MainWindow::slotTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        setVisible(!isVisible());
}


void MainWindow::createConnections()
{
    connect(ui.actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui.actionShowTrayIcon, SIGNAL(triggered(bool)), this, SLOT(slotShowTrayIcon(bool)));
    connect(ui.actionShowTrayIcon, SIGNAL(triggered(bool)), trayIcon, SLOT(setVisible(bool)));
    connect(ui.actionScan, SIGNAL(triggered(bool)), popupWidget, SLOT(slotScan(bool)));
    connect(ui.actionSettings, SIGNAL(triggered()), this, SLOT(slotSettings()));
    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));
    connect(ui.actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slotTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    connect(ui.treeWidget, SIGNAL(activateDictionary(Dictionary*)), ui.dictionaryWidget, SLOT(activateDictionary(Dictionary*)));
    connect(ui.treeWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
    connect(ui.dictionaryWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));

    connect(ui.treeWidget, SIGNAL(activateDictionary(Dictionary*)), popupWidget, SLOT(slotSetDictionary(Dictionary*)));

    ui.menu_Tools->insertAction(ui.actionSettings, ui.dockWidget->toggleViewAction());
    ui.menu_Tools->insertSeparator(ui.actionSettings);
}


void MainWindow::createTrayIcon()
{
    QMenu *trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(ui.actionScan);
    trayIconMenu->addSeparator();
/*     trayIconMenu->addAction(minimizeAction);
     trayIconMenu->addAction(maximizeAction);*/
    trayIconMenu->addAction(ui.actionSettings);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(ui.actionQuit);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/resources/qdictionary.png"));
    trayIcon->setToolTip(tr("QDictionary"));
    trayIcon->setVisible(_settings->showTrayIcon());
}


void MainWindow::readSettings()
{
    QSettings settings;

    settings.beginGroup("MainWindow");
    restoreState(settings.value("state", saveState()).toByteArray());
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    ui.actionShowTrayIcon->setChecked(settings.value("trayIcon", true).toBool());
    ui.actionScan->setChecked(settings.value("scan", true).toBool());
    settings.endGroup();

    trayIcon->setVisible(ui.actionShowTrayIcon->isChecked());
    ui.actionScan->setEnabled(ui.actionShowTrayIcon->isChecked());
    slotShowTrayIcon(ui.actionShowTrayIcon->isChecked());

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
    settings.setValue("trayIcon", ui.actionShowTrayIcon->isChecked());
    settings.setValue("scan", ui.actionScan->isChecked());
    settings.endGroup();

    settings.beginGroup("Dictionary");
    settings.setValue("dirs", _settings->dictDirs());
    settings.setValue("firstColor", _settings->firstColor());
    settings.setValue("secondColor", _settings->secondColor());
    settings.endGroup();
    ui.treeWidget->initDicts(_settings->dictDirs());

//    settings.beginGroup("Scan");

//    settings.endGroup();
}
