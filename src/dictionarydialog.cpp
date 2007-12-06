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
#include "dictionarydialog.h"

#include <QtGui>

#include "dictionarymodel.h"


DictionaryDialog::DictionaryDialog(QWidget *parent, DictionaryModel *d) : QDialog(parent), dict(d)
{
    ui.setupUi(this);

    if (dict)
    {
        ui.titleLineEdit->setText(dict->title());
        ui.authorLineEdit->setText(dict->author());
        ui.fileLineEdit->setText(dict->fileName());
        ui.oLangLineEdit->setText(dict->oLang());
        ui.tLangLineEdit->setText(dict->tLang());
    }
    connect(ui.fileToolButton, SIGNAL(clicked()), this, SLOT(slotFile()));
}


DictionaryModel *DictionaryDialog::newDictionary()
{
    DictionaryModel *dict = new DictionaryModel;
    dict->setTitle(ui.titleLineEdit->text());
    dict->setAuthor(ui.authorLineEdit->text());
    dict->setFileName(ui.fileLineEdit->text());
    dict->setOLang(ui.oLangLineEdit->text());
    dict->setTLang(ui.tLangLineEdit->text());

    return dict;
}


void DictionaryDialog::accept()
{
    if (dict)
    {
        dict->setTitle(ui.titleLineEdit->text());
        dict->setAuthor(ui.authorLineEdit->text());
        dict->setFileName(ui.fileLineEdit->text());
        dict->setOLang(ui.oLangLineEdit->text());
        dict->setTLang(ui.tLangLineEdit->text());
        dict->setSaved(false);
    }
    QDialog::accept();
}


void DictionaryDialog::slotFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return;

    ui.fileLineEdit->setText(fileName);
}
