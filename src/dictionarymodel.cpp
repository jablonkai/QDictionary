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
#include "dictionarymodel.h"

#include <QtGui>

#include "kvtmlreader.h"


DictionaryModel::DictionaryModel(QObject *parent) : QAbstractItemModel(parent)
{
}


DictionaryModel::DictionaryModel(const QString &name) : _fileName(name), _loaded(false)
{
}


DictionaryModel::~DictionaryModel()
{
}


QVariant DictionaryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    if (index.column() == 0)
        return dictionary.at(index.row()).original;
    else if (index.column() == 1)
        return dictionary.at(index.row()).translated;
}


QVariant DictionaryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section == 0)
        return _oLang;
    else if (section == 1)
        return _tLang;
    else return 0;
}


bool DictionaryModel::readInfo()
{
    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("QVocabulary"), QObject::tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return false;
    }

    KvtmlReader reader(this);
    return reader.readHeader(&file);
}


void DictionaryModel::load()
{
    dictionary.clear();

    QFile file(_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("QVocabulary"), QObject::tr("Cannot read file %1:\n%2.").arg(_fileName).arg(file.errorString()));
        return;
    }

    KvtmlReader reader(this);
    reader.read(&file);
    _loaded = true;
}


QString DictionaryModel::search(const QString &string, int index) const
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

//    QStandardItemModel *model = new QStandardItemModel(list.size(), 2, 0);
//    model->setHeaderData(0, Qt::Horizontal, _oLang);
//    model->setHeaderData(1, Qt::Horizontal, _tLang);
    QString result("<table cellspacing=2 cellpadding=3 border=0 align=\"center\">");
//<table cellspacing=2 cellpadding=3 border=0 align=\"center\">                     <tr><td colspan=3 align=\"center\">első <b>35</b> találat</td></tr>          <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutya&nbsp;&nbsp;<span class=\"szf\">költ.</span>&nbsp;&nbsp;<span class=\"szf\">táj.</span>&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">can&nbsp;<span class=\"szf\">(h)</span></td></tr>           <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutya&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">perro&nbsp;<span class=\"szf\">(h)</span></td></tr>              <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutya kötelessége&nbsp;&nbsp;<span class=\"szf\">biz.</span>&nbsp;&nbsp;<span class=\"szf\">[kifejezés]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">su deber elemental</td></tr>           <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutya kötelessége&nbsp;&nbsp;<span class=\"szf\">[kifejezés]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">su deber estricto</td></tr>             <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutya kötelessége&nbsp;&nbsp;<span class=\"szf\">biz.</span>&nbsp;&nbsp;<span class=\"szf\">[kifejezés]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">su estricto deber</td></tr>             <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutya nehéz munka&nbsp;&nbsp;<span class=\"szf\">átv.</span>&nbsp;&nbsp;<span class=\"szf\">[kifejezés]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">es un trabajo de negros</td></tr>              <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutya-&nbsp;&nbsp;<span class=\"szf\">átv.</span>&nbsp;&nbsp;<span class=\"szf\">[melléknév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">aperreado (, -a)</td></tr>               <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutya-&nbsp;&nbsp;<span class=\"szf\">[melléknév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">canino (, -a)</td></tr>                <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutya-&nbsp;&nbsp;<span class=\"szf\">[melléknév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">perro (, -a)</td></tr>               <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutya-&nbsp;&nbsp;<span class=\"szf\">[melléknév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">perruno (, -a)</td></tr>                <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutya-macska barátság&nbsp;&nbsp;<span class=\"szf\">átv.</span>&nbsp;&nbsp;<span class=\"szf\">[kifejezés]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">como perros y gatos</td></tr>           <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyabarát&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">perrero&nbsp;<span class=\"szf\">(h)</span></td></tr>                  <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyabőr&nbsp;&nbsp;<span class=\"szf\">tört.</span>&nbsp;&nbsp;<span class=\"szf\">biz.</span>&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">pergaminos&nbsp;<span class=\"szf\">(h tsz.)</span></td></tr>                   <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyaeledel&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">comida&nbsp;<span class=\"szf\">(n)</span> de pero</td></tr>                <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyaeledel&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">comida&nbsp;<span class=\"szf\">(n)</span> para perros</td></tr>          <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyaeledel&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">forraje&nbsp;<span class=\"szf\">(h)</span> de perro</td></tr>                <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyaeledel&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">pienso&nbsp;<span class=\"szf\">(h)</span> perruno</td></tr>                <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyaélet&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">vida&nbsp;<span class=\"szf\">(n)</span> aperrada</td></tr>               <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyaélet&nbsp;&nbsp;<span class=\"szf\">átv.</span>&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">vida&nbsp;<span class=\"szf\">(n)</span> aperreada</td></tr>                     <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyaélet&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">vida&nbsp;<span class=\"szf\">(n)</span> perra</td></tr>                   <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyaélet&nbsp;&nbsp;<span class=\"szf\">átv.</span>&nbsp;&nbsp;<span class=\"szf\">[kifejezés]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">una vida de perro</td></tr>                    <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyaélet&nbsp;&nbsp;<span class=\"szf\">átv.</span>&nbsp;&nbsp;<span class=\"szf\">[kifejezés]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">una vida de perros</td></tr>                       <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyafa&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">arraclán&nbsp;<span class=\"szf\">(h)</span></td></tr>                <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyafalka (pórázon tartott)&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">colla&nbsp;<span class=\"szf\">(n)</span></td></tr>             <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyafalka&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">jauría&nbsp;<span class=\"szf\">(n)</span></td></tr>                <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyafalka&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">perrada&nbsp;<span class=\"szf\">(n)</span></td></tr>                    <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyafalka&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">perrería&nbsp;<span class=\"szf\">(n)</span></td></tr>                   <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyafalka (vadászaton is)&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">recova&nbsp;<span class=\"szf\">(n)</span></td></tr>                 <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyafalka (vadászat)&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">traílla&nbsp;<span class=\"szf\">(n)</span></td></tr>                     <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyafuttában csinál&nbsp;&nbsp;<span class=\"szf\">[ige]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">chapucear</td></tr>                  <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyafuttában végez&nbsp;&nbsp;<span class=\"szf\">[ige]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">chapucear</td></tr>                        <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyafürdetés&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">ba&ntilde;amiento&nbsp;<span class=\"szf\">(h)</span> de perro</td></tr>                  <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyaketrec&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">perrera&nbsp;<span class=\"szf\">(n)</span></td></tr>                                    <tr><td width=270 height=18 class=\"sava\" bgcolor=\"#C0C0C0\">kutyakiállítás&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"sava\" bgcolor=\"#C0C0C0\">exposición&nbsp;<span class=\"szf\">(n)</span> canina</td></tr>                   <tr><td width=270 height=18 class=\"savb\" bgcolor=\"#C8C8C8\">kutyakölyök&nbsp;&nbsp;<span class=\"szf\">áll.</span>&nbsp;&nbsp;<span class=\"szf\">[főnév]</span></td><td width=2></td><td width=270 class=\"savb\" bgcolor=\"#C8C8C8\">cachorro&nbsp;<span class=\"szf\">(h)</span></td></tr>                        <tr><td colspan=3 height=\"70\" valign=\"bottom\" align=\"center\"><a href=bovlista.php?hu=kutya&d=0>&gt;bővítés&lt;</a></td></tr>                     </table>");
    bool b = true;
    QString color1("#C8C8C8");
    QString color2("#86CFFF");
    for (int i = 0; i < list.size(); ++i)
    {
        QString color = b ? "#6699FF" : "#6699CC";
        result +=  QString("<tr><td width=\"49%\" height=18 bgcolor=\"%1\">%2</td><td width=2></td><td width=\"49%\" bgcolor=\"%1\">%3</td></tr>").arg(color).arg(list.at(i).original).arg(list.at(i).translated);//.arg(color);
//        model->setData(model->index(i, 0, QModelIndex()), list.at(i).original);
//        model->setData(model->index(i, 1, QModelIndex()), list.at(i).translated);
        b = !b;
    }

//    return model;
    return result += "</table>";
}
