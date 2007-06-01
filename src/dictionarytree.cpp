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
	dictDir.cd("dict");
	
	foreach (QString fileName, dictDir.entryList(QDir::Files))
    {
    	Dictionary *d = new Dictionary(dictDir.absoluteFilePath(fileName));
//    	d.load(dictDir.absoluteFilePath(fileName));
//    	DictionaryReader reader(&d);
 //   	QFile file(dictDir.absoluteFilePath(fileName));
 //   	reader.read(&file);
//    	QString name = reader.readName(new QFile(dictDir.dirName() + fileName));
    	
		new DictionaryItem(dictionary, d->dictName(), d);
//		connect(ui.treeWidget, SIGNAL(itemActivated()), this, SLOT(dictChanged()));
/*        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin)
        {
            ModuleInterface *module = qobject_cast<ModuleInterface*>(plugin);
            if (module)
            {
                QAction *action = new QAction(QPixmap(":/data/new.png"), module->moduleName(), plugin);
                action->setStatusTip(module->statusTip());
                connect(action, SIGNAL(triggered()), this, SLOT(slotNew()));
                newMenu->addAction(action);
            }
        }*/
    }
//    newMenu->setEnabled(!newMenu->actions().isEmpty());
}


void DictionaryTree::itemActivate(QTreeWidgetItem *item, int)
{
	emit activateDictionary(static_cast<DictionaryItem*>(item)->dictionary);
}
