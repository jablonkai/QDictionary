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
#include "dictionarymanager.h"
#include "dictionarywidget.h"
#include "newdictionarydialog.h"
#include "popupwidget.h"
#include "settings.h"
#include "settingsdialog.h"


MainWindow::MainWindow() : QMainWindow()
{
    ui.setupUi(this);

    DictionaryManager::instance();

    createTrayIcon();
    popupWidget = new PopupWidget(this);
    createConnections();
    setupDictionaryTree();

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
        qApp->quit();
}


void MainWindow::slotNew()
{
    NewDictionaryDialog *dialog = new NewDictionaryDialog(this);

    if (dialog->exec() == QDialog::Accepted)
        DictionaryManager::instance()->addDictionary(dialog->newDictionary());
//        ui.treeWidget->addDictionary(dialog->newDictionary());

    delete dialog;
}


void MainWindow::slotSave()
{

}


void MainWindow::slotSetMode(QAction *action)
{
    if (action == ui.actionDictionary)
        ui.stackedWidget->setCurrentIndex(0);
//    else if (action == ui.actionVocabulary)
//        stackedWidget->setCurrentIndex(1);
    else if (action == ui.actionEdit)
        ui.stackedWidget->setCurrentIndex(1);
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
    Settings *settings = Settings::instance();

    settings->setTrayIconVisible(trayIcon->isVisible());
    settings->setScan(ui.actionScan->isChecked());

    SettingsDialog *dialog = new SettingsDialog(this);

    if (dialog->exec() == QDialog::Accepted)
    {
//        ui.treeWidget->updateSettings();
        ui.actionShowTrayIcon->setChecked(settings->isTrayIconVisible());
        ui.actionScan->setChecked(settings->scan());

        trayIcon->setVisible(ui.actionShowTrayIcon->isChecked());
        ui.actionScan->setEnabled(ui.actionShowTrayIcon->isChecked());
        slotShowTrayIcon(ui.actionShowTrayIcon->isChecked());
    }
    delete dialog;
}


void MainWindow::slotAbout()
{
    QMessageBox::about(this, tr("About QDictionary"), QString::fromUtf8("<b>QDictionary</b><br>Version " QDICTIONARY_VERSION "<br>Copyright (C) 2007 by Tamás Jablonkai<br><a href=\"mailto:tamas.jablonkai@gmail.com\">tamas.jablonkai@gmail.com</a>"));
}


void MainWindow::slotTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        setVisible(!isVisible());
}


void MainWindow::updateWidgets()
{
    ui.dictionaryWidget->updateWidget();
    ui.editWidget->updateWidget();
//    ui.stackedWidget->currentWidget();
}


void MainWindow::createConnections()
{
    connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(slotNew()));
    connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(slotSave()));
    connect(ui.actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QActionGroup *modeGroup = new QActionGroup(this);
    modeGroup->addAction(ui.actionDictionary);
//    modeGroup->addAction(ui.actionVocabulary);
    modeGroup->addAction(ui.actionEdit);
    connect(modeGroup, SIGNAL(triggered(QAction*)), this, SLOT(slotSetMode(QAction*)));
    connect(ui.actionShowTrayIcon, SIGNAL(triggered(bool)), this, SLOT(slotShowTrayIcon(bool)));
    connect(ui.actionShowTrayIcon, SIGNAL(triggered(bool)), trayIcon, SLOT(setVisible(bool)));
    connect(ui.actionScan, SIGNAL(triggered(bool)), popupWidget, SLOT(slotScan(bool)));
    connect(ui.actionSettings, SIGNAL(triggered()), this, SLOT(slotSettings()));
    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));
    connect(ui.actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slotTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    connect(DictionaryManager::instance(), SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
    connect(DictionaryManager::instance(), SIGNAL(update()), this, SLOT(updateWidgets()));
    connect(ui.dictionaryWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));
    connect(ui.editWidget, SIGNAL(statusBarMessage(QString, int)), ui.statusBar, SLOT(showMessage(QString, int)));

    ui.menu_Tools->insertAction(ui.actionSettings, ui.dockWidget->toggleViewAction());
    ui.menu_Tools->insertSeparator(ui.actionSettings);
}


void MainWindow::createTrayIcon()
{
    QMenu *trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(ui.actionScan);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(ui.actionSettings);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(ui.actionQuit);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/resources/qdictionary.png"));
    trayIcon->setToolTip(tr("QDictionary"));
}


void MainWindow::setupDictionaryTree()
{
    ui.treeWidget->header()->hide();
    QTreeWidgetItem *dictRoot = DictionaryManager::instance()->dictionaryRoot();
    ui.treeWidget->insertTopLevelItem(0, dictRoot);
    ui.treeWidget->expandItem(dictRoot);

    connect(ui.treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*, int)), DictionaryManager::instance(), SLOT(itemActivated(QTreeWidgetItem*)));
}


void MainWindow::readSettings()
{
    QSettings conf;

    conf.beginGroup("MainWindow");
    restoreState(conf.value("state", saveState()).toByteArray());
    restoreGeometry(conf.value("geometry", saveGeometry()).toByteArray());
    ui.actionShowTrayIcon->setChecked(conf.value("trayIcon", true).toBool());
    conf.value("hide", false).toBool() ? hide() : show();
    ui.actionScan->setChecked(conf.value("scan", false).toBool());
    conf.endGroup();

    trayIcon->setVisible(ui.actionShowTrayIcon->isChecked());
    ui.actionScan->setEnabled(ui.actionShowTrayIcon->isChecked());
    slotShowTrayIcon(ui.actionShowTrayIcon->isChecked());
    if (!ui.actionShowTrayIcon->isChecked())
        show();

//    ui.treeWidget->updateSettings();
}


void MainWindow::writeSettings()
{
    QSettings conf;

    conf.beginGroup("MainWindow");
    conf.setValue("state", saveState());
    conf.setValue("geometry", saveGeometry());
    conf.setValue("trayIcon", ui.actionShowTrayIcon->isChecked());
    conf.setValue("hide", isHidden());
    conf.setValue("scan", ui.actionScan->isChecked());
    conf.endGroup();
}
