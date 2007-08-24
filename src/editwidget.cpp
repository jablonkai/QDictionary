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
#include "editwidget.h"

#include <QtGui>

#include "dictionary.h"


EditWidget::EditWidget()
{
    ui.setupUi(this);

    connect(ui.addButton, SIGNAL(clicked()), this, SLOT(slotAdd()));
    connect(ui.resetButton, SIGNAL(clicked()), this, SLOT(slotReset()));
}


void EditWidget::activateDictionary(Dictionary *d)
{
    dict = d;

    ui.label1->setText(dict->oLang() + ":");
    ui.label2->setText(dict->tLang() + ":");
    ui.lineEdit1->clear();
    ui.lineEdit2->clear();

    updateList();
}



void EditWidget::slotAdd()
{
    dict->entryList().append(Entry(ui.lineEdit1->text(), ui.lineEdit2->text()));
    ui.lineEdit1->clear();
    ui.lineEdit2->clear();

    updateList();
}


void EditWidget::slotReset()
{
/*    int row = ui.tableView->selectedIndexes().first().row();
    dict->entryList().removeAll(Entry(dict->entryList().at(row).original, dict->entryList().at(row).translated));
    updateList();*/
//    removeAt();
}


void EditWidget::updateList()
{
    model = new QStandardItemModel(dict->entryList().size(), 2, this);
    model->setHeaderData(0, Qt::Horizontal, dict->oLang());
    model->setHeaderData(1, Qt::Horizontal, dict->tLang());
    for (int i = 0; i < dict->entryList().size(); ++i)
    {
        model->setData(model->index(i, 0, QModelIndex()), dict->entryList().at(i).original);
        model->setData(model->index(i, 1, QModelIndex()), dict->entryList().at(i).translated);
    }
    ui.tableView->setModel(model);
}
