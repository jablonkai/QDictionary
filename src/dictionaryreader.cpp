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
#include "dictionaryreader.h"

#include "dictionary.h"


DictionaryReader::DictionaryReader(QIODevice *device, Dictionary *d) : QXmlStreamReader(device), dict(d)
{
}


DictionaryReader::~DictionaryReader()
{
}


void DictionaryReader::readUnknownElement()
{
    while (!atEnd())
    {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement())
            readUnknownElement();
    }
}


bool DictionaryReader::readHeader()
{
    while (!atEnd())
    {
        readNext();

        if (isStartElement())
        {
            if (name() == "xdict")
            {
                dict->setTitle(attributes().value("title").toString());
                dict->setAuthor(attributes().value("author").toString());
                dict->setOLang(attributes().value("original").toString());
                dict->setTLang(attributes().value("translated").toString());
                return true;
            }
            else
                raiseError(QObject::tr("The file is not a XDICT file."));
        }
    }
    return !error();
}


bool DictionaryReader::read()
{
    while (!atEnd())
    {
        readNext();

        if (isStartElement())
        {
            if (name() == "xdict")
                readRoot();
            else
                raiseError(QObject::tr("The file is not a XDICT file."));
        }
    }
    return !error();
}


void DictionaryReader::readRoot()
{
    while (!atEnd())
    {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement())
        {
            if (name() == "e")
                readEntry();
            else if (name() == "lesson")
                ;
            else
                readUnknownElement();
        }
    }
}


void DictionaryReader::readEntry()
{
    QString o, t;

    while (!atEnd())
    {
        readNext();

        if (isEndElement())
            break;

        else if (isStartElement())
        {
            if (name() == "o")
                o = readElementText();
            else if (name() == "t")
                t = readElementText();
            else
                readUnknownElement();
        }
    }
    dict->entryList().append(Entry(o, t));
}
