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
#include "dictionarymodel.h"

#include <QtGui>

#include "dictionaryreader.h"


DictionaryModel::DictionaryModel(QObject *parent) : QAbstractItemModel(parent)
{
}


DictionaryModel::DictionaryModel(const QString &name) : _fileName(name), _loaded(false)
{
    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("QVocabulary"), QObject::tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return;
    }

    DictionaryReader reader(this);
    reader.readHeader(&file);
}


DictionaryModel::~DictionaryModel()
{
}


QVariant DictionaryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    if (index.column() == 0)
        return dictionary.at(index.row()).original;
    else if (index.column() == 1)
        return dictionary.at(index.row()).translated;
}


QVariant DictionaryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section == 0)
        return _oLang;
    else if (section == 1)
        return _tLang;
    else return 0;
}


void DictionaryModel::load()
{
    dictionary.clear();

    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("QVocabulary"), QObject::tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return;
    }

    DictionaryReader reader(this);
    reader.read(&file);
    _loaded = true;
}


QStandardItemModel *DictionaryModel::search(const QString &string, int index) const
{
    QList<Entry> list;

    if (index == 0)
        foreach (Entry i, dictionary)
            if (i.original.contains(string, Qt::CaseInsensitive))
                list << i;
    if (index == 1)
        foreach (Entry i, dictionary)
            if (i.translated.contains(string, Qt::CaseInsensitive))
                list << i;

    QStandardItemModel *model = new QStandardItemModel(list.size(), 2, 0);
    model->setHeaderData(0, Qt::Horizontal, _oLang);
    model->setHeaderData(1, Qt::Horizontal, _tLang);

    for (int i = 0; i < list.size(); ++i)
    {
        model->setData(model->index(i, 0, QModelIndex()), list.at(i).original);
        model->setData(model->index(i, 1, QModelIndex()), list.at(i).translated);
    }

    return model;
}
