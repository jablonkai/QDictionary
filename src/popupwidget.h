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
#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QWidget>


class QTextBrowser;


class PopupWidget : public QWidget
{
    Q_OBJECT

public:
    PopupWidget(QWidget *parent = 0);
    ~PopupWidget();

public slots:
    void slotScan(bool);

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void timerEvent(QTimerEvent*);

private:
    void search();

    QTextBrowser *textBrowser;
    QTimer *closeTimer;
    QString prevSelection;
    int timerId;
};


#endif
