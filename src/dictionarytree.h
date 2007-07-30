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
#ifndef DICTIONARYTREE_H
#define DICTIONARYTREE_H

#include <QTreeWidget>


class Dictionary;


class DictionaryTree : public QTreeWidget
{
    Q_OBJECT

public:
    DictionaryTree(QWidget*);

    void initDicts(const QStringList&);

signals:
    void statusBarMessage(QString, int);
    void activateDictionary(Dictionary*);

private slots:
    void itemActivate(QTreeWidgetItem*, int);

private:
    QTreeWidgetItem *dictionaries;
    QTreeWidgetItem *vocabulary;
};


#endif
