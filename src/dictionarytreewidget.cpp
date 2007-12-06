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
#include "dictionarytreewidget.h"

#include <QtGui>

#include "dictionarymanager.h"
#include "dictionarymodel.h"
#include "mainwindow.h"


DictionaryTreeWidget::DictionaryTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
}


DictionaryTreeWidget::~DictionaryTreeWidget()
{
}


void DictionaryTreeWidget::init(MainWindow *main)
{
    mainWindow = main;

    header()->hide();
    QTreeWidgetItem *dictRoot = DictionaryManager::instance()->dictionaryRoot();
    insertTopLevelItem(0, dictRoot);
    expandItem(dictRoot);

    connect(this, SIGNAL(itemActivated(QTreeWidgetItem*, int)), DictionaryManager::instance(), SLOT(itemActivated(QTreeWidgetItem*)));

    loadAct = new QAction(tr("Load"), this);
    connect(loadAct, SIGNAL(triggered()), this, SLOT(slotLoad()));

    saveAct = new QAction(QIcon(":/resources/save.png"), tr("Save"), this);
    saveAct->setStatusTip(mainWindow->ui.actionSave->statusTip());
    connect(saveAct, SIGNAL(triggered()), this, SLOT(slotSave()));

    unloadAct = new QAction(tr("Unload"), this);
    connect(unloadAct, SIGNAL(triggered()), this, SLOT(slotUnload()));
}


void DictionaryTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    DictionaryModel *dict = static_cast<DictionaryModel*>(itemAt(event->pos()));
    if (!dict)
        return;

    QMenu menu(this);
    menu.addMenu(mainWindow->ui.menu_Mode);
    menu.addSeparator();
    if (dict->isLoaded())
    {
        if (!dict->isSaved())
            menu.addAction(saveAct);
        menu.addAction(unloadAct);
    }
//void DictionaryTree::slotLoad()
/*     newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
     newAct->setShortcut(tr("Ctrl+N"));
     newAct->setStatusTip(tr("Create a new file"));
     connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));*/
    else
        menu.addAction(loadAct);
//    ui.actionDictionary->isChecked() ? menu.addAction(ui.actionEdit) : menu.addAction(ui.actionDictionary);

    menu.addAction(new QAction("gdf", this));
    menu.addAction(new QAction("dfh", this));

    menu.exec(event->globalPos());
}


void DictionaryTreeWidget::slotLoad()
{
    DictionaryManager::instance()->itemActivated(selectedItems().first());
}


void DictionaryTreeWidget::slotSave()
{
    static_cast<DictionaryModel*>(selectedItems().first())->save();
}


void DictionaryTreeWidget::slotUnload()
{
//    static_cast<DictionaryModel*>(selectedItems().first())->unload();
    DictionaryManager::instance()->itemDeactivated(selectedItems().first());
}
