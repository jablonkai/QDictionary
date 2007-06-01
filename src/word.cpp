#include "word.h"

#include <QDomDocument>


Word::Word(QString o, QString t) : original(o), translated(t)
{
}


Word::Word(const QDomElement &element)
{
	original = element.firstChildElement("o").text();
	translated = element.firstChildElement("t").text();
}


QDomElement Word::createXMLNode(QDomDocument &doc)
{
	QDomElement element = doc.createElement("w");
	
	QDomElement o = doc.createElement("o");
	o.appendChild(doc.createTextNode(original));
	element.appendChild(o);
	QDomElement t = doc.createElement("t");
	t.appendChild(doc.createTextNode(translated));
	element.appendChild(t);

	return element;
}
