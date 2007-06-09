#include "dictionarywidget.h"

#include <QtGui>

#include "dictionary.h"


DictionaryWidget::DictionaryWidget()
{
    ui.setupUi(this);

    connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(slotSearch()));
    connect(ui.searchButton, SIGNAL(released()), this, SLOT(slotSearch()));
}


void DictionaryWidget::activateDictionary(Dictionary *d)
{
    dict = d;

    ui.comboBox->clear();
    ui.lineEdit->clear();
    ui.tableView->setModel(0);

    ui.comboBox->addItem(QString("%1 -> %2").arg(dict->oLang()).arg(dict->tLang()));
    ui.comboBox->addItem(QString("%1 -> %2").arg(dict->tLang()).arg(dict->oLang()));
}


void DictionaryWidget::slotSearch()
{
    QTime time;
    time.start();
    QList<Entry> d = dict->search(ui.lineEdit->text(), ui.comboBox->currentIndex());

    QStandardItemModel *model = new QStandardItemModel(d.size(), 2, this);
    model->setHeaderData(0, Qt::Horizontal, dict->oLang());
    model->setHeaderData(1, Qt::Horizontal, dict->tLang());

    for (int i = 0; i < d.size(); ++i)
    {
        model->setData(model->index(i, 0, QModelIndex()), d.at(i).original);
        model->setData(model->index(i, 1, QModelIndex()), d.at(i).translated);
    }

    ui.tableView->setModel(model);
    ui.tableView->sortByColumn(0, Qt::AscendingOrder);
    ui.tableView->resizeColumnsToContents();

    emit statusBarMessage(tr("The number of results: %1\t(Within %2 sec)").arg(d.size()).arg(time.elapsed() / 1000.0f), 0);
}
