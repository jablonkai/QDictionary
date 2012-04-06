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

#include <Qt/QtWidgets>

#include "dictionaryreader.h"
#include "dictionarywriter.h"
#include "entry.h"


DictionaryModel::DictionaryModel(QObject *parent) : QAbstractItemModel(parent), QTreeWidgetItem(1001), loaded(true), saved(false)
{
    setIcon(0, QIcon(":/resources/save.png"));
}


DictionaryModel::DictionaryModel(const QString &fileName, QObject *parent) : QAbstractItemModel(parent), QTreeWidgetItem(1001), _fileName(fileName), loaded(false), saved(true)
{
}


DictionaryModel::~DictionaryModel()
{
    if (!saved)
        save();
}


QVariant DictionaryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= list.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
    {
        if (index.column() == 0)
            return list.at(index.row()).original;
        if (index.column() == 1)
            return list.at(index.row()).translated;
    }
    else
        return QVariant();
}


QVariant DictionaryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        if (section == 0)
            return _oLang;
        if (section == 1)
            return _tLang;
    }
    else
        return QString("%1").arg(section);
}


Qt::ItemFlags DictionaryModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


bool DictionaryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        if (index.column() == 0)
            list[index.row()].original = value.toString();
        if (index.column() == 1)
            list[index.row()].translated = value.toString();
        emit dataChanged(index, index);
        saved = false;
        return true;
    }
    return false;
}


bool DictionaryModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    endInsertRows();
    saved = false;
    return true;
}


bool DictionaryModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        list.removeAt(position);

    endRemoveRows();
    saved = false;
    return true;
}


bool DictionaryModel::addEntry(const Entry &entry)
{
    insertRows(rowCount(QModelIndex()), 1);
    list.append(entry);
    setSaved(false);
}


void DictionaryModel::updateInfo()
{
    setText(0, _title);
    setToolTip(0, QString("<b>%1</b><br>Author: %2<br>Original: %3<br>Translated: %4").arg(_title).arg(_author).arg(_oLang).arg(_tLang));
}










bool DictionaryModel::readInfo()
{
    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(0, tr("QDictionary"), tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return false;
    }

    DictionaryReader reader(&file, this);
    bool b = reader.readHeader();

    if (b)
        updateInfo();

    return b;
}


void DictionaryModel::load()
{
    if (loaded)
        return;

    list.clear();

    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(0, tr("QDictionary"), tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return;
    }

    DictionaryReader reader(&file, this);
    reader.read();
    loaded = true;

    setIcon(0, QIcon(":/resources/qdictionary.png"));
}


void DictionaryModel::unload()
{
    if (!saved)
    {
        int ret = QMessageBox::warning(0, tr("QDictionary"), tr("The dictionary has been modified.\nDo you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
        switch (ret)
        {
            case QMessageBox::Save:
                save();
                break;
            case QMessageBox::Cancel:
                return;
            default:
                break;
        }
    }
    list.clear();
    setIcon(0, QIcon(""));
    loaded = false;
}


void DictionaryModel::save()
{
    if (saved)
        return;

    QFile file(_fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(0, tr("QDictionary"), tr("Cannot write file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return;
    }

    DictionaryWriter writer(&file, this);
    writer.write();
    setSaved(true);
}


void DictionaryModel::append(const Entry &e)
{
    list.append(e);
    saved = false;
}


void DictionaryModel::setSaved(bool b)
{
    saved = b;
    if (saved)
        setIcon(0, QIcon(":/resources/qdictionary.png"));
    else
        setIcon(0, QIcon(":/resources/save.png"));
}
