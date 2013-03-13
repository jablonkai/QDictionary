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
#ifndef DICTIONARYMODEL_H
#define DICTIONARYMODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtWidgets/QTreeWidgetItem>


class Entry;


class DictionaryModel : public QAbstractItemModel, public QTreeWidgetItem
{
    Q_OBJECT

public:
    DictionaryModel(QObject *parent = 0);
    DictionaryModel(const QString &fileName, QObject *parent = 0);
    ~DictionaryModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const { return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex(); }
    QModelIndex parent(const QModelIndex&) const { return QModelIndex(); }
    int columnCount (const QModelIndex&) const { return 2; }
    int rowCount(const QModelIndex&) const { return list.count(); }
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool addEntry(const Entry&);
    void updateInfo();

private:
    QList<Entry> list;

public:
    bool readInfo();
    void load();
    void unload();
    void save();
    QTreeWidgetItem *getTreeWidgetItem();

    void setFileName(const QString &s) { _fileName = s; }
    QString fileName() const { return _fileName; }

    void setTitle(const QString &s) { _title = s; }
    QString title() const { return _title; }

    void setAuthor(const QString &s) { _author = s; }
    QString author() const { return _author; }

    void setOLang(const QString &s) { _oLang = s; }
    QString oLang() const { return _oLang; }

    void setTLang(const QString &s) { _tLang = s; }
    QString tLang() const { return _tLang; }

    QList<Entry> &entryList() { return list; }
    void append(const Entry&);

    void setSaved(bool b);
    bool isSaved() const { return saved; }
    bool isLoaded() const { return loaded; }

private:
    QString _title;
    QString _author;
    QString _oLang;
    QString _tLang;
    QString _fileName;

    bool loaded;
    bool saved;
};


#endif
