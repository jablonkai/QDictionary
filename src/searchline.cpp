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


SearchLine::SearchLine(QWidget *parent) : QLineEdit(parent)
{
    clearButton = new QLabel(this);
    clearButton->setAlignment( Qt::AlignLeft | Qt::AlignVCenter );
    clearButton->setPixmap(QPixmap("./src/clear.png"));
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setToolTip(tr("Clear text"));
    clearButton->hide();

//    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() +  1));

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
//    QSize msz = minimumSizeHint();
 //   setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2),
   //                qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));

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
}/*LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    clearButton = new QToolButton(this);
    QPixmap pixmap("./src/clear.png");
    clearButton->setIcon(QIcon(pixmap));
    clearButton->setIconSize(pixmap.size());
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    clearButton->hide();
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2),
                   qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));
}

void LineEdit::resizeEvent(QResizeEvent *)
{
    QSize sz = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - sz.width(),
                      (rect().bottom() + 1 - sz.height())/2);
}

void LineEdit::updateCloseButton(const QString& text)
{
    clearButton->setVisible(!text.isEmpty());
}*/


