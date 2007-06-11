#include "dictionarywidget.h"

#include <QtGui>

#include "dictionary.h"


DictionaryWidget::DictionaryWidget()
{
    ui.setupUi(this);

    filterModel = new QSortFilterProxyModel(this);
    filterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    filterModel->setDynamicSortFilter(true);
    filterModel->setSortLocaleAware(true),
    filterModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui.tableView->setModel(filterModel);

    connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(slotSearch()));
    connect(ui.searchButton, SIGNAL(released()), this, SLOT(slotSearch()));
    connect(ui.filteringCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotFiltering(bool)));
    connect(ui.filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilter()));
    connect(ui.filterLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotFilter()));
    connect(ui.filterCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotFilter()));
    connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(slotItemActivated(const QModelIndex&)));

    ui.filterWidget->setVisible(false);
}


void DictionaryWidget::activateDictionary(Dictionary *d)
{
    dict = d;

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

    emit statusBarMessage(tr("The number of results: %1\t(Within %2 sec)").arg(d.size()).arg(time.elapsed() / 1000.0f), 0);
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
