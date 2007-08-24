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
#ifndef NEWDICTIONARYDIALOG_H
#define NEWDICTIONARYDIALOG_H

#include <QDialog>

#include "ui_newdictionarydialog.h"


class Dictionary;


class NewDictionaryDialog : public QDialog
{
    Q_OBJECT

public:
    NewDictionaryDialog(QWidget *parent = 0);
    ~NewDictionaryDialog();

    Dictionary *newDictionary();

public slots:
    virtual void accept();

private slots:
    void slotFile();

private:
    Ui::NewDictionaryDialog ui;
    Dictionary *dict;
};


#endif
