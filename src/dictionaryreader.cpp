#include "dictionaryreader.h"

#include "dictionary.h"


DictionaryReader::DictionaryReader(Dictionary *d) : dict(d)
{
}


bool DictionaryReader::read(QIODevice *device)
{
	setDevice(device);

	while (!atEnd())
	{
		readNext();

		if (isStartElement())
		{
			if (name() == "qvoc")
				readRoot();
			else
				raiseError(QObject::tr("The file is not an QVOC file."));
		}
	}
	
//	QMessageBox::information(0, QString("%1").arg(error()), errorString());
	return !error();
}


void DictionaryReader::readUnknownElement()
{
	Q_ASSERT(isStartElement());
	
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
	Q_ASSERT(isStartElement() && name() == "qvoc");

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
	Q_ASSERT(isStartElement() && name() == "header");

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
	Q_ASSERT(isStartElement() && name() == "lang");
	
	dict->setOLang(attributes().value("from").toString());
	dict->setTLang(attributes().value("to").toString());

	readNext();						// kell ez ide???
}


void DictionaryReader::readDict()
{
	Q_ASSERT(isStartElement() && name() == "dict");

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
	Q_ASSERT(isStartElement() && name() == "w");

	QString o, t;
	while (!atEnd())
	{
		readNext();
		
		if (isEndElement())
			break;
			
		else if (isStartElement())				// jobbat !!!!!!!!!
		{
			if (name() == "o")
				o = readElementText();
			else if (name() == "t")
				t = readElementText();
			else
				readUnknownElement();
		}
	}
	dict->dictionary << Word(o, t);
}
