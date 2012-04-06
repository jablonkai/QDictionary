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
#include "dictionarymanager.h"

#include <Qt/QtGui>
#include <Qt/QtCore>

#include "dictionarymodel.h"
#include "settings.h"


DictionaryManager::DictionaryManager(QObject *parent) : QObject(parent)
{
    readSettings();
    dictRoot = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Dictionaries")), 1000);

    int i = 0;
    foreach (QString dir, _dictDirs)
    {
        QDir dictDir = QDir(dir);

        foreach (QString fileName, dictDir.entryList(QDir::Files))
        {
            DictionaryModel *dict = new DictionaryModel(dictDir.absoluteFilePath(fileName));
            if (dict->readInfo())
            {
                dictionaries.append(dict);
                dictRoot->addChild(dict);
                ++i;
            }
        }
    }

    emit statusBarMessage(tr("%1 dictionaries loaded").arg(i), 0);
}


DictionaryManager::~DictionaryManager()
{
    writeSettings();
}


void DictionaryManager::addDictionary(DictionaryModel *dict)
{
    dictionaries.append(dict);
    dictRoot->addChild(dict);
    itemActivated(dict);
}


void DictionaryManager::itemDeactivated(QTreeWidgetItem *item)
{
    if (item->type() == 1001)
    {
        DictionaryModel *_item = static_cast<DictionaryModel*>(item);
        if (_item == activeDict)
            activeDict = 0;
        _item->unload();
        emit update();
    }
}


void DictionaryManager::itemActivated(QTreeWidgetItem *item)
{
    if (item->type() == 1001)
    {
        activeDict = static_cast<DictionaryModel*>(item);
        activeDict->load();
        emit update();
    }
}


void DictionaryManager::readSettings()
{
    QSettings settings;

    settings.beginGroup("Dictionary");
/*    _dictDirs = settings.value("dirs", QApplication::instance()->applicationDirPath() + "/dict").toStringList();
    settings.endGroup();

    foreach (QString i, _dictDirs)
        if (QApplication::instance()->applicationDirPath() + "/dict" == i)
            return;
    _dictDirs += QApplication::instance()->applicationDirPath() + "/dict";*/
}


void DictionaryManager::writeSettings()
{
    QSettings settings;

    settings.beginGroup("Dictionary");
    settings.setValue("dirs", _dictDirs);
    settings.endGroup();
}
