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

#include "dictionarymodel.h"


EditWidget::EditWidget()
{
    ui.setupUi(this);

    connect(ui.addButton, SIGNAL(clicked()), this, SLOT(slotAdd()));
    connect(ui.resetButton, SIGNAL(clicked()), this, SLOT(slotReset()));
}


void EditWidget::activateDictionary(DictionaryModel *d)
{
    dict = d;

    ui.oLang->setText(dict->oLang());
    ui.tLang->setText(dict->tLang());

    updateList();
}



void EditWidget::slotAdd()
{
//    dict->dictionary << Entry(ui.oLang->text(), ui.tLang->text());

//    QStandardItem item
    //model->appendColumn();//setData(model->index(i, 0, QModelIndex()), ui.oLang->text());
  //  model->setData(model->index(i, 1, QModelIndex()), ui.tLang->text());
//	dict->add(ui.lineEdit1->text(), ui.lineEdit2->text());
//	updateList();
//	model->setData(model->index(i, 0, QModelIndex()), dict->dictionary.last().first);
//	model->setData(model->index(i, 1, QModelIndex()), dict->dictionary.last().second);
}


void EditWidget::slotReset()
{
}


void EditWidget::updateList()
{
/*    model = new QStandardItemModel(dict->dictionary.size(), 2, this);
    model->setHeaderData(0, Qt::Horizontal, dict->oLang());
    model->setHeaderData(1, Qt::Horizontal, dict->tLang());

    for (int i = 0; i < dict->dictionary.size(); ++i)
    {
        model->setData(model->index(i, 0, QModelIndex()), dict->dictionary.at(i).original);
        model->setData(model->index(i, 1, QModelIndex()), dict->dictionary.at(i).translated);
    }

    ui.tableView->setModel(model);*/
}
