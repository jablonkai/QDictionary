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
    connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(slotItemActivated(const QModelIndex&)));

    ui.filterWidget->setVisible(false);


    ui.textBrowser->setHtml("<strong><span lang=\"en-US\">apple</span></strong> <span><em>főnév</em></span><br><strong>1. alma</strong><span>: </span>kerek, kemény húsú, lédús gyümölcs, amelynek zöld, sárga vagy piros héja és kis magjai vannak. <em><span lang=\"en-US\">Give me an apple</span>. (Adj egy almát!)<span lang=\"en-US\"><br></span></em><strong>2.</strong> <strong>almafa</strong><span>: </span>az a fa, amin ez a gyümölcs terem. <em><span lang=\"en-US\">We have some apples in the garden</span>. (Van néhány almafánk a <span lang=\"hu-HU\">kertben.</span><span lang=\"en-US\">)</span>");
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
