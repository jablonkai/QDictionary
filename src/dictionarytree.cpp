#include "dictionarytree.h"

#include <QtGui>

#include "dictionary.h"


class DictionaryItem : public QTreeWidgetItem
{
public:
	DictionaryItem(QTreeWidgetItem *parent, QString text, Dictionary *d) : QTreeWidgetItem(parent, QStringList(text)), dictionary(d) {}
	
	Dictionary *dictionary;
};


DictionaryTree::DictionaryTree(QWidget *parent) : QTreeWidget(parent)
{
	header()->hide();
	
	dictionary = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Dictionary")));
	insertTopLevelItem(0, dictionary);
	
	initDicts();
	
	connect(this, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(itemActivate(QTreeWidgetItem*, int)));
}


void DictionaryTree::initDicts()
{
	QDir dictDir = QDir(qApp->applicationDirPath());
	dictDir.cd("../dict");
	
	foreach (QString fileName, dictDir.entryList(QDir::Files))
    {
    	Dictionary *d = new Dictionary(dictDir.absoluteFilePath(fileName));
		new DictionaryItem(dictionary, d->dictName(), d);
    }
    expandItem(dictionary);
}


void DictionaryTree::itemActivate(QTreeWidgetItem *item, int)
{
	emit activateDictionary(static_cast<DictionaryItem*>(item)->dictionary);
}
