#include "dictionary.h"

#include <QtGui>

#include "dictionaryreader.h"


Dictionary::Dictionary(QString name) : _fileName(name), _loaded(false)
{
    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("QVocabulary"), QObject::tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return;
    }

    DictionaryReader reader(this);
    reader.readHeader(&file);
//    load();
}


void Dictionary::load()
{
    dictionary.clear();

    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("QVocabulary"), QObject::tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return;
    }

    DictionaryReader reader(this);
    reader.read(&file);
    _loaded = true;
}


QList<Entry> Dictionary::search(QString string, int index)
{
    QList<Entry> list;

    if (index == 0)
        foreach (Entry i, dictionary)
            if (i.original.contains(string, Qt::CaseInsensitive))
                list << i;
    if (index == 1)
        foreach (Entry i, dictionary)
            if (i.translated.contains(string, Qt::CaseInsensitive))
                list << i;

    return list;
}
