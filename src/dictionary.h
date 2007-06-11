#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QList>

#include "entry.h"


class Dictionary
{
public:
    Dictionary(const QString&);

    QList<Entry> dictionary;

    void setOLang(const QString&);
    QString oLang() const;
    void setTLang(const QString&);
    QString tLang() const;
    void setDictName(const QString&);
    QString dictName() const;

    QString fileName() const;

    bool loaded() const;
    void setLoaded(bool);

    void load();

    QList<Entry> search(const QString&, int) const;

private:
    QString _oLang;
    QString _tLang;
    QString _dictName;

    QString _fileName;
    bool _loaded;
};


inline void Dictionary::setOLang(const QString &s)
{
    _oLang = s;
}


inline QString Dictionary::oLang() const
{
    return _oLang;
}


inline void Dictionary::setTLang(const QString &s)
{
    _tLang = s;
}


inline QString Dictionary::tLang() const
{
    return _tLang;
}


inline void Dictionary::setDictName(const QString &s)
{
    _dictName = s;
}


inline QString Dictionary::dictName() const
{
    return _dictName;
}


inline QString Dictionary::fileName() const
{
    return _fileName;
}


inline bool Dictionary::loaded() const
{
    return _loaded;
}


inline void Dictionary::setLoaded(bool b)
{
    _loaded = b;
}


#endif
