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


KvtmlReader::KvtmlReader() : QXmlStreamReader()
{
}


KvtmlReader::~KvtmlReader()
{
}
/*DictionaryReader::DictionaryReader(DictionaryModel *d) : dict(d)
{
}


bool DictionaryReader::readHeader(QIODevice *device)
{
    setDevice(device);

    while (!atEnd())
    {
        readNext();

        if (isStartElement())
        {
            if (name() == "xdict")
                while (!atEnd())
                {
                    readNext();

                    if (isEndElement())
                        break;

                    if (isStartElement())
                    {
                        if (name() == "header")
                            readHeader();
                        else if (name() == "dict")
                            break;
                        else
                            readUnknownElement();
                    }
                }
            else
                raiseError(QObject::tr("The file is not an XDICT file."));
        }
    }
    return !error();
}


bool DictionaryReader::read(QIODevice *device)
{
    setDevice(device);

    while (!atEnd())
    {
        readNext();

        if (isStartElement())
        {
            if (name() == "xdict")
                readRoot();
            else
                raiseError(QObject::tr("The file is not an XDICT file."));
        }
    }

//  QMessageBox::information(0, QString("%1").arg(error()), errorString());
    return !error();
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


void DictionaryReader::readRoot()
{
    while (!atEnd())
    {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement())
        {
            if (name() == "header")
                readHeader();
            else if (name() == "dict")
                readDict();
            else
                readUnknownElement();
        }
    }
}


void DictionaryReader::readHeader()
{
    while (!atEnd())
    {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement())
        {
            if (name() == "doc_type")
                QString type = readElementText();
            else if (name() == "lang")
                readLang();
            else if (name() == "dict_name")
                dict->setDictName(readElementText());
            else
                readUnknownElement();
        }
    }
}


void DictionaryReader::readLang()
{
    dict->setOLang(attributes().value("from").toString());
    dict->setTLang(attributes().value("to").toString());

    readNext();
}


void DictionaryReader::readDict()
{
    while (!atEnd())
    {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement())
        {
            if (name() == "w" || name() == "e")
                readWord();
            else
                readUnknownElement();
        }
    }
}


void DictionaryReader::readWord()
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
    dict->push_back(Entry(o, t));
}
*/