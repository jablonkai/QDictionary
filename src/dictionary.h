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

#include <QTreeWidgetItem>


class Entry
{
public:
    Entry(const QString &o, const QString &t) : original(o), translated(t) {}

    QString original;
    QString translated;
};


class Dictionary : public QTreeWidgetItem
{
public:
    Dictionary();
    Dictionary(const QString&);
    ~Dictionary();

    bool readInfo();
    void load();
    void save();
    QList<Entry> search(const QString&, int) const;
    QString popupSearch(const QString&) const;
    QTreeWidgetItem *getTreeWidgetItem();

    void setFileName(const QString &s) { _fileName = s; }

    void setTitle(const QString &s) { _title = s; }
    QString title() const { return _title; }

    void setAuthor(const QString &s) { _author = s; }
    QString author() const { return _author; }

    void setOLang(const QString &s) { _oLang = s; }
    QString oLang() const { return _oLang; }

    void setTLang(const QString &s) { _tLang = s; }
    QString tLang() const { return _tLang; }

    QList<Entry> &entryList() { return dictionary; }
    void append(const Entry&);

private:
    QString _title;
    QString _author;
    QString _oLang;
    QString _tLang;
    QString _fileName;

    bool loaded;
    bool saved;
    QList<Entry> dictionary;
};


#endif
