#include "dictionarywidget.h"

#include <QtGui>

#include "dictionary.h"


DictionaryWidget::DictionaryWidget()
{
	ui.setupUi(this);
	
	slotFiltering(Qt::Unchecked);
	
	connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(slotSearch()));
	connect(ui.filteringCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotFiltering(int)));
//	connect(ui.eraseButton, SIGNAL(clicked()), ui.lineEdit, SLOT(clear()));
}


void DictionaryWidget::activateDictionary(Dictionary *d)
{
	dict = d;
	
	ui.comboBox->clear();
	ui.comboBox->addItem(QString("%1 -> %2").arg(dict->oLang()).arg(dict->tLang()));
	ui.comboBox->addItem(QString("%1 -> %2").arg(dict->tLang()).arg(dict->oLang()));
	
	ui.filterComboBox->clear();
	ui.filterComboBox->addItem(QString("%1").arg(dict->oLang()));
	ui.filterComboBox->addItem(QString("%1").arg(dict->tLang()));
}


void DictionaryWidget::slotSearch()
{
	QTime time;
	time.start();
	QList<Entry> d = dict->search(ui.lineEdit->text(), ui.comboBox->currentIndex());
	emit statusBarMessage(tr("The number of results: %1\t(Within %2 sec)").arg(d.size()).arg(time.elapsed() / 1000.0f), 0);
		
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
}


void DictionaryWidget::slotFiltering(int state)			// vastag csíkot eltüntetni ha nem aktív
{
	bool visible = (state == Qt::Checked) ? true : false;
	
	ui.filterLabel->setVisible(visible);
	ui.filterComboBox->setVisible(visible);
	ui.filterLineEdit->setVisible(visible);
	ui.filterCheckBox->setVisible(visible);
}


void slotFilter()
{
}
