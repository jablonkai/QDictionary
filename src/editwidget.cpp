#include "editwidget.h"

#include <QtGui>

#include "dictionary.h"


EditWidget::EditWidget()
{
    ui.setupUi(this);

    connect(ui.addButton, SIGNAL(clicked()), this, SLOT(slotAdd()));
    connect(ui.resetButton, SIGNAL(clicked()), this, SLOT(slotReset()));

    updateList();
}


void EditWidget::activateDictionary(Dictionary *d)
{
    dict = d;
    updateList();
}



void EditWidget::slotAdd()
{
//	dict->add(ui.lineEdit1->text(), ui.lineEdit2->text());
	updateList();
//	model->setData(model->index(i, 0, QModelIndex()), dict->dictionary.last().first);
//	model->setData(model->index(i, 1, QModelIndex()), dict->dictionary.last().second);
}


void EditWidget::slotReset()
{

}


void EditWidget::updateList()
{
/*	model = new QStandardItemModel(dict->dictionary.size(), 2, this);
	model->setHeaderData(0, Qt::Horizontal, tr("Magyar"));
	model->setHeaderData(1, Qt::Horizontal, tr("Angol"));

	for (int i = 0; i < dict->dictionary.size(); ++i)
	{
		model->setData(model->index(i, 0, QModelIndex()), dict->dictionary.at(i).first);
		model->setData(model->index(i, 1, QModelIndex()), dict->dictionary.at(i).second);
	}

	ui.tableView->setModel(model);*/
}
