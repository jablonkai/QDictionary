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
#include "searchline.h"

#include <QtGui>


static char *clearPixmap[]={
"22 22 13 1",
". c None",
"# c #000000",
"k c #181818",
"j c #2d2d2d",
"i c #404040",
"h c #5a5a5a",
"g c #696969",
"e c #888888",
"d c #939393",
"b c #b7b7b7",
"a c #bdbdbd",
"c c #cfcfcf",
"f c #ffffff",
"......................",
"......................",
"......................",
"......................",
"......................",
"......................",
"........##########....",
".......#aabbabbac#....",
"......#deffedeffe#....",
".....#gghfffhfffh#....",
"....#iiiijfffffji#....",
"...#kkkkkk#fff#kk#....",
"...f######fffff###....",
"....f####fff#fff##....",
".....f###ff###ff##....",
"......f###########....",
".......f##########....",
"........ffffffffff....",
"......................",
"......................",
"......................",
"......................"};


SearchLine::SearchLine(QWidget *parent) : QLineEdit(parent)
{
    clearButton = new QLabel(this);
    clearButton->setAlignment( Qt::AlignLeft | Qt::AlignVCenter );
    clearButton->setPixmap(QPixmap(clearPixmap));
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setToolTip(tr("Clear text"));
    clearButton->hide();

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));

    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));
}


void SearchLine::mousePressEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton || event->button() == Qt::MidButton ) && clearButton->underMouse())
        clear();

    QLineEdit::mousePressEvent(event);
}


void SearchLine::resizeEvent(QResizeEvent*)
{
    QSize size = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - size.width(), (rect().bottom() + 1 - size.height())/2);
}


void SearchLine::updateCloseButton(const QString& text)
{
    clearButton->setVisible(!text.isEmpty());
}
