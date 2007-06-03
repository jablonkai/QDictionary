#include "dictionarywidget.h"

#include <QtGui>

#include "dictionary.h"


DictionaryWidget::DictionaryWidget()
{
	ui.setupUi(this);
	/*
it simply was not doable in qt since there wasn't enough flexibility in qlineedit
without resorting to really fugly hacks (like including and using private api from
qlineedit). well, qt's new css styled widgets to the rescue! now i can just do:

setStyleSheet(QString(":enabled { padding-right: %1; }").arg(buttonWidth));

where buttonWidth is the width of the clear button and voila ... no more text under
the button. this gives us:*/
//	ui.lineEdit->setStyleSheet(QString(":enabled { padding-right: %1; }").arg(ui.eraseButton->width()));
	ui.clearButton->setParent(ui.lineEdit);
	
	connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(slotSearch()));
//	connect(ui.eraseButton, SIGNAL(clicked()), ui.lineEdit, SLOT(clear()));
}


void DictionaryWidget::activateDictionary(Dictionary *d)
{
	dict = d;
	
	ui.comboBox->clear();
	ui.comboBox->addItem(QString("%1 -> %2").arg(dict->oLang()).arg(dict->tLang()));
	ui.comboBox->addItem(QString("%1 -> %2").arg(dict->tLang()).arg(dict->oLang()));
}


void DictionaryWidget::slotSearch()
{
	QTime time;
	time.start();
	QList<Word> d = dict->search(ui.lineEdit->text(), ui.comboBox->currentIndex());
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
