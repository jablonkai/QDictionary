#ifndef DICTIONARYTREE_H
#define DICTIONARYTREE_H

#include <QTreeWidget>


class Dictionary;


class DictionaryTree : public QTreeWidget
{
	Q_OBJECT
	
public:
	DictionaryTree(QWidget*);
	
signals:
	void activateDictionary(Dictionary*);
	
private:
	QTreeWidgetItem *dictionary;
	QTreeWidgetItem *vocabulary;
	
	void initDicts();
	
private slots:
	void itemActivate(QTreeWidgetItem*, int);
};


#endif
