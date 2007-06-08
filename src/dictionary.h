#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QList>

#include "entry.h"


class Dictionary
{
public:
	Dictionary(QString);
	
	QList<Entry> dictionary;

	void setOLang(QString);
	QString oLang();
	void setTLang(QString);
	QString tLang();
	void setDictName(QString);
	QString dictName();
		
	QString fileName();
		
	void load();
	
	QList<Entry> search(QString, int);

private:
	QString _oLang;
	QString _tLang;
	QString _dictName;
	
	QString _fileName;
};


inline void Dictionary::setOLang(QString s)
{
	_oLang = s;
}


inline QString Dictionary::oLang()
{
	return _oLang;
}


inline void Dictionary::setTLang(QString s)
{
	_tLang = s;
}


inline QString Dictionary::tLang()
{
	return _tLang;
}


inline void Dictionary::setDictName(QString s)
{
	_dictName = s;
}


inline QString Dictionary::dictName()
{
	return _dictName;
}


inline QString Dictionary::fileName()
{
	return _fileName;
}


#endif
