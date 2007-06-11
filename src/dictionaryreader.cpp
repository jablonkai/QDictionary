#include "dictionaryreader.h"

#include "dictionary.h"


DictionaryReader::DictionaryReader(Dictionary *d) : dict(d)
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
    dict->dictionary << Entry(o, t);
}
