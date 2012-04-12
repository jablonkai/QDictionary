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
#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include "ui_editwidget.h"


QT_FORWARD_DECLARE_CLASS(QStandardItemModel)


class EditWidget : public QWidget
{
    Q_OBJECT

public:
    EditWidget();

public slots:
    void updateWidget();

signals:
    void statusBarMessage(QString, int);

protected:
    void showEvent(QShowEvent*);

private slots:
    void slotAdd();
    void slotSave();
    void slotDelete();
    void slotDocSettings();
    void slotSelected(const QModelIndex&);

private:
    void updateDictionary();

    Ui::EditWidget ui;
    QStandardItemModel *model;
};


#endif
