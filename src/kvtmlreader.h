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
#ifndef KVTMLREADER_H
#define KVTMLREADER_H

#include <QXmlStreamReader>


class KvtmlReader : public QXmlStreamReader
{
public:
    KvtmlReader();
    ~KvtmlReader();
};/*class DictionaryReader : public QXmlStreamReader
{
public:
    DictionaryReader(DictionaryModel*);

    bool readHeader(QIODevice*);
    bool read(QIODevice*);

private:
    void readUnknownElement();
    void readRoot();
    void readHeader();
    void readLang();
    void readDict();
    void readWord();

    DictionaryModel *dict;
};*/
/*<!--
This is a machine generated file.
Be careful when editing here.

Short definition:

lesson       lesson group
 desc        name
   %no       its index
   %query    is in query selection
   %current  is current lesson
type         type group
 desc        name
   %no       its index
e            entry of dictionary
  %s         is selected
  %m         lesson member
  %t         common expression type
 o           original
   %q        in query ("o" is given, "t" is wanted)
   %l        language code
   %r        remark
   %p        pronunciation
   %width    column width
   %t        expression type (see QueryManager.h)
   %tf       false friend from
   %ff       false friend to
   %a        antonym
   %y        synonym
   %x        example
   %u        usage label
   %h        paraphrase
 t           translation ..
   %q        in query ("t" is given, "o" is wanted)
   %l        language code
   %r        remark
   %p        pronunciation
   %width    column width
   %t        expression type
   %tf       false friend from
   %ff       false friend to
   %a        antonym
   %y        synonym
   %x        example
   %u        usage label
   %h        paraphrase

   %d        last query date (from;to)
   %w        dito, compressed and deprecated
   %g        grade (from;to)
   %c        count (from;to)
   %b        bad count (from;to)


Valid xml means:
 - Close all tags
 - Keep proper hierarchy
 - All attributes are quoted
-->*/


#endif
