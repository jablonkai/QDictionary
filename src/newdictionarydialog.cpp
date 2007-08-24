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
#include "newdictionarydialog.h"

#include <QtGui>

#include "dictionary.h"


NewDictionaryDialog::NewDictionaryDialog(QWidget *parent) : QDialog(parent), dict(0)
{
    ui.setupUi(this);

    connect(ui.fileToolButton, SIGNAL(clicked()), this, SLOT(slotFile()));
}


NewDictionaryDialog::~NewDictionaryDialog()
{
}


Dictionary *NewDictionaryDialog::newDictionary()
{
    return dict;
}


void NewDictionaryDialog::accept()
{
    dict = new Dictionary;

    dict->setTitle(ui.titleLineEdit->text());
    dict->setAuthor(ui.authorLineEdit->text());
    dict->setFileName(ui.fileLineEdit->text());
    dict->setOLang(ui.oLangLineEdit->text());
    dict->setTLang(ui.tLangLineEdit->text());

    QDialog::accept();
}


void NewDictionaryDialog::slotFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return;

    ui.fileLineEdit->setText(fileName);
}
