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
#include "dictionarywidget.h"

#include <QtGui>

#include "dictionary.h"
#include "settings.h"


class SearchCommand : public QUndoCommand
{
public:
    SearchCommand(const QString &prev, const int &prevI, const QString &s, const int &i, DictionaryWidget *w) : prevText(prev), prevIndex(prevI), text(s), index(i), widget(w) {}

    virtual void undo() { if (prevIndex <= 1) widget->search(prevText, prevIndex); }
    virtual void redo() { widget->search(text, index); }

private:
    QString prevText;
    QString text;
    int prevIndex;
    int index;
    DictionaryWidget *widget;
};


DictionaryWidget::DictionaryWidget(QWidget *parent) : QWidget(parent), dict(0), prevText(""), prevIndex(100)
{
    ui.setupUi(this);

    undoStack = new QUndoStack(this);

    filterModel = new QSortFilterProxyModel(this);
    filterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    filterModel->setDynamicSortFilter(true);
    filterModel->setSortLocaleAware(true),
    filterModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui.tableView->setModel(filterModel);

    connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(slotSearch()));
    connect(ui.searchButton, SIGNAL(clicked()), this, SLOT(slotSearch()));
    connect(ui.filteringCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotFiltering(bool)));
    connect(ui.filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilter()));
    connect(ui.filterLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotFilter()));
    connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(slotItemActivated(const QModelIndex&)));
    connect(ui.backwardButton, SIGNAL(clicked()), undoStack, SLOT(undo()));
    connect(ui.forwardButton, SIGNAL(clicked()), undoStack, SLOT(redo()));
    connect(undoStack, SIGNAL(canUndoChanged(bool)), ui.backwardButton, SLOT(setEnabled(bool)));
    connect(undoStack, SIGNAL(canRedoChanged(bool)), ui.forwardButton, SLOT(setEnabled(bool)));

    ui.filterWidget->setVisible(false);
}


void DictionaryWidget::init(Settings *settings)
{
    QPalette palette = ui.tableView->palette();                         // nem jó !!!!!!!!!!!44
    palette.setColor(QPalette::Base, settings->firstColor());
    palette.setColor(QPalette::AlternateBase, settings->firstColor());
    ui.tableView->setPalette(palette);
}


void DictionaryWidget::search(const QString &s, const int &i)
{
    ui.lineEdit->setText(s);
    ui.comboBox->setCurrentIndex(i);

    QList<Entry> d = dict->search(ui.lineEdit->text(), ui.comboBox->currentIndex());

    QStandardItemModel *model = new QStandardItemModel(d.size(), 2, this);
    model->setHeaderData(0, Qt::Horizontal, dict->oLang());
    model->setHeaderData(1, Qt::Horizontal, dict->tLang());

    for (int i = 0; i < d.size(); ++i)
    {
        model->setData(model->index(i, 0, QModelIndex()), d.at(i).original);
        model->setData(model->index(i, 1, QModelIndex()), d.at(i).translated);
    }

    filterModel->setSourceModel(model);
    ui.tableView->sortByColumn(ui.comboBox->currentIndex(), Qt::AscendingOrder);
    ui.tableView->resizeColumnsToContents();

    n = d.size();
}


void DictionaryWidget::activateDictionary(Dictionary *d)
{
    dict = d;
    undoStack->clear();
    prevIndex = 100;

    ui.comboBox->clear();
    ui.lineEdit->clear();
    ui.comboBox->addItem(QString("%1 -> %2").arg(dict->oLang()).arg(dict->tLang()));
    ui.comboBox->addItem(QString("%1 -> %2").arg(dict->tLang()).arg(dict->oLang()));

    ui.filterComboBox->clear();
    ui.filterLineEdit->clear();
    ui.filterComboBox->addItem(QString("%1").arg(dict->oLang()));
    ui.filterComboBox->addItem(QString("%1").arg(dict->tLang()));
}


void DictionaryWidget::slotSearch()
{
    if (!dict)
        return;

    QTime time;
    time.start();

    QString text = ui.lineEdit->text();
    int index = ui.comboBox->currentIndex();

    undoStack->push(new SearchCommand(prevText, prevIndex, text, index, this));
    prevText = text;
    prevIndex = index;

    emit statusBarMessage(tr("The number of results: %1\t(Within %2 sec)").arg(n).arg(time.elapsed() / 1000.0f), 0);
}


void DictionaryWidget::slotFiltering(bool b)
{
    b ? slotFilter() : filterModel->setFilterRegExp(0);
}


void DictionaryWidget::slotFilter()
{
    filterModel->setFilterKeyColumn(ui.filterComboBox->currentIndex());
    filterModel->setFilterRegExp(QRegExp(ui.filterLineEdit->text(), Qt::CaseInsensitive, QRegExp::Wildcard));
}


void DictionaryWidget::slotItemActivated(const QModelIndex &index)
{
    ui.comboBox->setCurrentIndex(index.column());
    ui.lineEdit->setText(index.data().toString());
    slotSearch();

    ui.filterLineEdit->clear();
    slotFilter();
}
