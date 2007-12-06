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

#include "dictionarydialog.h"
#include "dictionarymanager.h"
#include "entry.h"


EditWidget::EditWidget()
{
    ui.setupUi(this);

    connect(ui.addButton, SIGNAL(clicked()), this, SLOT(slotAdd()));
    connect(ui.saveButton, SIGNAL(clicked()), this, SLOT(slotSave()));
    connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(slotDelete()));
    connect(ui.toolButton, SIGNAL(clicked()), this, SLOT(slotDocSettings()));
    connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(slotSelected(const QModelIndex&)));
}


void EditWidget::updateWidget()
{
    if (this->isVisible())
        updateDictionary();
}


void EditWidget::showEvent(QShowEvent*)
{
    updateDictionary();
}


void EditWidget::slotAdd()
{
    DictionaryModel *dict = DictionaryManager::instance()->activeDictionary();
    if (!dict || ui.lineEdit1->text().isEmpty() || ui.lineEdit1->text().isEmpty())
        return;

    dict->addEntry(Entry(ui.lineEdit1->text(), ui.lineEdit2->text()));

    ui.lineEdit1->clear();
    ui.lineEdit2->clear();
}


void EditWidget::slotSave()
{
    DictionaryModel *dict = DictionaryManager::instance()->activeDictionary();
    if (!dict || !ui.tableView->currentIndex().isValid())
        return;

    int i = ui.tableView->currentIndex().row();
    dict->entryList().replace(i, Entry(ui.lineEdit1->text(), ui.lineEdit2->text()));
    dict->setSaved(false);
}


void EditWidget::slotDelete()
{
    DictionaryModel *dict = DictionaryManager::instance()->activeDictionary();
    if (!dict)
        return;

    dict->removeRow(ui.tableView->selectionModel()->selectedIndexes().first().row());
    dict->setSaved(false);
}


void EditWidget::slotDocSettings()
{
    DictionaryModel *dict = DictionaryManager::instance()->activeDictionary();
    if (!dict)
        return;

    DictionaryDialog *dialog = new DictionaryDialog(this, dict);
    if (dialog->exec() == QDialog::Accepted)
        updateDictionary();
    delete dialog;
    DictionaryManager::instance()->activeDictionary()->updateInfo();
}


void EditWidget::slotSelected(const QModelIndex&)
{
    int i = ui.tableView->currentIndex().row();
    DictionaryModel *dict = DictionaryManager::instance()->activeDictionary();

    ui.lineEdit1->setText(dict->entryList().at(i).original);
    ui.lineEdit2->setText(dict->entryList().at(i).translated);
}


void EditWidget::updateDictionary()
{
    ui.lineEdit1->clear();
    ui.lineEdit2->clear();
    ui.tableView->setModel(0);
    ui.label1->setText(tr("First language:"));
    ui.label2->setText(tr("Second language:"));

    DictionaryModel *dict = DictionaryManager::instance()->activeDictionary();
    if (!dict)
        return;
    ui.tableView->setModel(dict);
    ui.label1->setText(dict->oLang() + ":");
    ui.label2->setText(dict->tLang() + ":");
}
