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
#ifndef DICTIONARYWIDGET_H
#define DICTIONARYWIDGET_H

#include "ui_dictionarywidget.h"


QT_FORWARD_DECLARE_CLASS(QSortFilterProxyModel)
QT_FORWARD_DECLARE_CLASS(QUndoStack)

class SearchModel;


class DictionaryWidget : public QWidget
{
    Q_OBJECT

public:
    DictionaryWidget();

    void search(const QString&, const int&);

public slots:
    void updateWidget();

signals:
    void statusBarMessage(QString, int);

protected:
    void showEvent(QShowEvent*);

private slots:
    void slotSearch();
    void slotFiltering(bool);
    void slotFilter();
    void slotItemActivated(const QModelIndex&);

private:
    void updateDictionary();

    Ui::DictionaryWidget ui;

    QSortFilterProxyModel *filterModel;
    SearchModel *searchModel;
    QUndoStack *undoStack;
    QString prevText;
    int prevIndex;
    int n;
};


#endif
