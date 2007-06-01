#ifndef DICTIONARYREADER_H
#define DICTIONARYREADER_H

#include <QXmlStreamReader>


class Dictionary;


class DictionaryReader : public QXmlStreamReader
{
public:
	DictionaryReader(Dictionary*);
	
	bool read(QIODevice*);
	
private:
	void readUnknownElement();
	void readRoot();
	void readHeader();
	void readLang();
	void readDict();
	void readWord();
	
	Dictionary *dict;
};


#endif
