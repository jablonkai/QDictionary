#include "dictionarytree.h"

#include <QtGui>

#include "dictionary.h"


class DictionaryItem : public QTreeWidgetItem
{
public:
	DictionaryItem(QTreeWidgetItem *parent, QString text, Dictionary *d) : QTreeWidgetItem(parent, QStringList(text)), dictionary(d) {}
	~DictionaryItem() { delete dictionary; }
	
	Dictionary *dictionary;
};


DictionaryTree::DictionaryTree(QWidget *parent) : QTreeWidget(parent)
{
	header()->hide();
	
	dictionaries = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Dictionaries")));
	insertTopLevelItem(0, dictionaries);
	
	initDicts();
	
	connect(this, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(itemActivate(QTreeWidgetItem*, int)));
}


void DictionaryTree::initDicts()
{
	QDir dictDir = QDir(qApp->applicationDirPath());
	dictDir.cd("dict");
	
	int i = 0;
	foreach (QString fileName, dictDir.entryList(QDir::Files))
    {
    	Dictionary *d = new Dictionary(dictDir.absoluteFilePath(fileName));
		new DictionaryItem(dictionaries, d->dictName(), d);
		++i;
    }
    expandItem(dictionaries);
    
    emit statusBarMessage(tr("%1 dictionaries loaded").arg(i), 0);
}


void DictionaryTree::itemActivate(QTreeWidgetItem *item, int)
{
	if (dictionaries == item)
		return;
	
	emit activateDictionary(static_cast<DictionaryItem*>(item)->dictionary);
}
