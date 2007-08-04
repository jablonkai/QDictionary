/***************************************************************************
 *   Copyright (C) 2007 by Jablonkai Tamás                                 *
 *   tamas.jablonkai@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "dictionarytree.h"

#include <QtGui>

#include "dictionary.h"
#include "settings.h"


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

    connect(this, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(itemActivate(QTreeWidgetItem*, int)));
}


void DictionaryTree::itemActivate(QTreeWidgetItem *item, int)
{
    if (dictionaries == item)
        return;

    Dictionary *dict = static_cast<DictionaryItem*>(item)->dictionary;
    if (!dict->loaded())
        dict->load();

    emit activateDictionary(dict);
}


void DictionaryTree::updateSettings()
{
    dictionaries->takeChildren();

    int i = 0;
    foreach (QString dir, Settings::Instance()->dictDirs())
    {
        QDir dictDir = QDir(dir);

        foreach (QString fileName, dictDir.entryList(QDir::Files))
        {
            Dictionary *d = new Dictionary(dictDir.absoluteFilePath(fileName));
            if (d->readInfo())
            {
                new DictionaryItem(dictionaries, d->dictName(), d);
                ++i;
            }
        }
    }
    expandItem(dictionaries);

    emit statusBarMessage(tr("%1 dictionaries loaded").arg(i), 0);
}
