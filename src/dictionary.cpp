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


/*QVariant Dictionary::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    if (index.column() == 0)
        return dictionary.at(index.row()).original;
    else if (index.column() == 1)
        return dictionary.at(index.row()).translated;
}


QVariant Dictionary::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section == 0)
        return _oLang;
    else if (section == 1)
        return _tLang;
    else return 0;
}*/


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


QString Dictionary::search(const QString &string, int index, const QColor &color1, const QColor &color2) const
{
    QString result("<table cellspacing=2 cellpadding=3 border=0 align=\"center\">");
    bool b = true;
    if (index == 0)
        foreach (Entry i, dictionary)
            if (i.original.contains(string, Qt::CaseInsensitive))
            {
                QString color = b ? color1.name() : color2.name();
                result +=  QString("<tr><td width=\"49%\" height=18 bgcolor=\"%1\"><a href=\"%2://%3\">%3</a></td><td width=2></td><td width=\"49%\" bgcolor=\"%1\"><a href=\"%4://%5\">%5</a></td></tr>").arg(color).arg(_oLang).arg(i.original).arg(_tLang).arg(i.translated);
                b = !b;
            }
    if (index == 1)
        foreach (Entry i, dictionary)
            if (i.translated.contains(string, Qt::CaseInsensitive))
            {
                QString color = b ? color1.name() : color2.name();
                result +=  QString("<tr><td width=\"49%\" height=18 bgcolor=\"%1\"><a href=\"%2://%3\">%3</a></td><td width=2></td><td width=\"49%\" bgcolor=\"%1\"><a href=\"%4://%5\">%5</a></td></tr>").arg(color).arg(_oLang).arg(i.original).arg(_tLang).arg(i.translated);
                b = !b;
            }

    return result += "</table>";
}
