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
#include "dictionary.h"

#include <QtGui>

#include "kvtmlreader.h"


Dictionary::Dictionary(const QString &name) : _fileName(name), _loaded(false)
{
}


Dictionary::~Dictionary()
{
}


bool Dictionary::readInfo()
{
    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("QVocabulary"), QObject::tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return false;
    }

    KvtmlReader reader(this);
    return reader.readHeader(&file);
}


void Dictionary::load()
{
    dictionary.clear();

    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("QVocabulary"), QObject::tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return;
    }

    KvtmlReader reader(this);
    reader.read(&file);
    _loaded = true;
}


QList<Entry> Dictionary::search(const QString &string, int index) const
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

    return list;
}


QString Dictionary::popupSearch(const QString &string) const
{
    QString text = QString("<strong>%1</strong><hr/>").arg(string);

    QList<Entry> firstList;
    QList<Entry> secondList;
    foreach (Entry i, dictionary)
    {
        if (i.original == string)
            firstList << i;
        if (i.translated == string)
            secondList << i;
    }

    if (!firstList.empty())
    {
        text += QString("<em><u>%1 - %2</u></em><br/>").arg(_oLang).arg(_tLang);
        foreach (Entry i, firstList)
            text += QString("%1<br/>").arg(i.translated);
    }

    if (!secondList.empty())
    {
        text += QString("<em><u>%1 - %2</u></em><br/>").arg(_tLang).arg(_oLang);
        foreach (Entry i, secondList)
            text += QString("%1<br/>").arg(i.original);
    }

    return text;
}
