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
#include "kvtmlreader.h"

#include "dictionarymodel.h"


KvtmlReader::KvtmlReader(DictionaryModel *d) : dict(d)
{
}


KvtmlReader::~KvtmlReader()
{
}


void KvtmlReader::readUnknownElement()
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


bool KvtmlReader::readHeader(QIODevice *device)
{
    setDevice(device);

    while (!atEnd())
    {
        readNext();

        if (isStartElement())
        {
            if (name() == "kvtml")
            {
//                dict->setDictName(attributes().value("encoding").toString());
//                dict->setDictName(attributes().value("generator").toString());
//                dict->setDictName(attributes().value("cols").toString());
//                dict->setDictName(attributes().value("lines").toString());
                dict->setDictName(attributes().value("title").toString());
//                dict->setDictName(attributes().value("author").toString());
                return true;
            }
/*  encoding="UTF-8"
  generator="kvoctrain v0.8.2"
  cols="2"
  lines="5014"
  title="SAT"
  author="http://www.freevocabulary.com">*/
            else
                raiseError(QObject::tr("The file is not a KVTML file."));
        }
    }
    return !error();
}


bool KvtmlReader::read(QIODevice *device)
{
    setDevice(device);

    while (!atEnd())
    {
        readNext();

        if (isStartElement())
        {
            if (name() == "kvtml")
            {
//                dict->setDictName(attributes().value("encoding").toString());
//                dict->setDictName(attributes().value("generator").toString());
//                dict->setDictName(attributes().value("cols").toString());
//                dict->setDictName(attributes().value("lines").toString());
//                dict->setDictName(attributes().value("title").toString());
//                dict->setDictName(attributes().value("author").toString());
                readRoot();
            }
            else
                raiseError(QObject::tr("The file is not a KVTML file."));
        }
    }
    return !error();
}


void KvtmlReader::readRoot()
{
    while (!atEnd())
    {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement())
        {
            if (name() == "e")
                readElement();
            else if (name() == "lesson");
            else if (name() == "options");
            else
                readUnknownElement();
        }
    }
}


void KvtmlReader::readElement()
{
    QString o, t;
    while (!atEnd())
    {
        readNext();

        if (isEndElement())
            break;

        else if (isStartElement())          // ha egysorban van minden akkor nem olvasa be !!!
        {
            if (name() == "o")
                o = readElementText();
            else if (name() == "t")
                t = readElementText();
            else
                readUnknownElement();
        }
    }
    dict->push_back(Entry(o, t));
}
