#ifndef WORD_H
#define WORD_H

#include <QString>


class QDomDocument;
class QDomElement;


class Word
{
public:
	QString original;
	QString translated;
	
	Word(QString, QString);
	Word(const QDomElement&);

	QDomElement createXMLNode(QDomDocument&);
};


#endif
