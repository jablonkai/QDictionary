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
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QList>
#include <QString>


class Entry
{
public:
    Entry(const QString &o, const QString &t) : original(o), translated(t) {}

    QString original;
    QString translated;
};


class Dictionary
{
public:
//    DictionaryModel(QObject *parent = 0);
    Dictionary(const QString&);
    ~Dictionary();

/*    int rowCount(const QModelIndex &parent = QModelIndex()) const { return parent.isValid() ? 0 : dictionary.size(); }
    int columnCount(const QModelIndex &parent = QModelIndex()) const { return parent.isValid() ? 0 : 2; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex parent(const QModelIndex & index) const { return QModelIndex(); }
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const { return hasIndex(row, column, parent) ? createIndex(row, column, 0) : QModelIndex(); }*/

    bool readInfo();
    void load();
    QString search(const QString&, int) const;

    void setDictName(const QString &s) { _dictName = s; }
    QString dictName() const { return _dictName; }
    void setOLang(const QString &s) { _oLang = s; }
    QString oLang() const { return _oLang; }
    void setTLang(const QString &s) { _tLang = s; }
    QString tLang() const { return _tLang; }
    bool loaded() const { return _loaded; }
    void setLoaded(bool b) { _loaded = b; }
    void push_back(const Entry &e) { dictionary << e; }

private:
    QString _fileName;
    QString _oLang;
    QString _tLang;
    QString _dictName;
    bool _loaded;

    QList<Entry> dictionary;
};


#endif
