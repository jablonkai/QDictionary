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
#include "popupwidget.h"

#include <QtGui>

#include "dictionary.h"


PopupWidget::PopupWidget(QWidget *parent) : QWidget(parent, Qt::Popup)/*Qt::ToolTip)*/, dict(0)
{
    textBrowser = new QTextBrowser(this);

    closeTimer = new QTimer(this);
    connect(closeTimer, SIGNAL(timeout()), this, SLOT(close()));
    connect(closeTimer, SIGNAL(timeout()), closeTimer, SLOT(stop()));

    hide();
}


PopupWidget::~PopupWidget()
{
}


void PopupWidget::slotSetDictionary(Dictionary *d)
{
    dict = d;
}


void PopupWidget::slotScan(bool b)
{
    if (b)
    {
        prevSelection = qApp->clipboard()->text(QClipboard::Selection);
        timerId = startTimer(300);
    }
    else
        killTimer(timerId);
}


void PopupWidget::enterEvent(QEvent*)
{
    closeTimer->stop();
}


void PopupWidget::leaveEvent(QEvent*)
{
    closeTimer->start(200);
}


void PopupWidget::timerEvent(QTimerEvent*)
{
    QString selection = qApp->clipboard()->text(QClipboard::Selection);
    if (prevSelection != selection)
    {
        prevSelection = selection;
        search();
    }
}


void PopupWidget::search()
{
    if (!dict)
        return;

    textBrowser->setHtml(dict->popupSearch(prevSelection));
    textBrowser->adjustSize();
    move(cursor().pos() - QPoint(30, 30));
    show();
/*    if (m_modifierKey && ! Keyboard::activeModifiers().testFlag(static_cast<Qt::KeyboardModifier>(m_modifierKey)))
        return ;
    QString m_source = QApplication::clipboard()->text(QClipboard::Selection);
    m_source.remove(QRegExp("^\\W"));
    m_source.remove(QRegExp("\\W.*$"));
    if (m_showIfNotFound || m_dict->isTranslatable(m_source))
    {
        QString translated = m_dict->translate(m_source, true);
        translationView->setHtml(translated);
        translationView->adjustSize();
        move(cursor().pos() - QPoint(30, 30));
        show();
    }*/
}
/*#include "popupwindow.h"

PopupWindow::PopupWindow(DictCore *dict, QWidget *parent)
        : QWidget(parent, Qt::ToolTip)
{
    if (! dict)
        m_dict = new DictCore(this);
    else
        m_dict = dict;
    translationView = new QTextBrowser(this);

    timerId = 0;

    QSettings config;
    setScan(config.value("PopupWindow/scan", true).toBool());
    setModifierKey(config.value("PopupWindow/modifierKey", 0).toInt());
    setShowIfNotFound(config.value("PopupWindow/showIfNotFound", false).toBool());
    setWindowOpacity(config.value("PopupWindow/opacity", 1.0).toDouble());
}

PopupWindow::~PopupWindow()
{
    QSettings config;
    config.setValue("PopupWindow/scan", m_scan);
    config.setValue("PopupWindow/modifierKey", m_modifierKey);
    config.setValue("PopupWindow/showIfNotFound", m_showIfNotFound);
    config.setValue("PopupWindow/opacity", windowOpacity());
}

void PopupWindow::setScan(bool scan)
{
    if (m_scan == scan)
        return ;
    m_scan = scan;
    if (m_scan)
    {
        lastSelection = QApplication::clipboard()->text(QClipboard::Selection);
        timerId = startTimer(300);
    }
    else
        killTimer(timerId);
    emit scanChanged(scan);
}

bool PopupWindow::isScan() const
{
    return m_scan;
}

void PopupWindow::setModifierKey(int key)
{
    m_modifierKey = key;
}

int PopupWindow::modifierKey() const
{
    return m_modifierKey;
}

bool PopupWindow::showIfNotFound() const
{
    return m_showIfNotFound;
}

void PopupWindow::setShowIfNotFound(bool mode)
{
    m_showIfNotFound = mode;
}

DictCore* PopupWindow::dict() const
{
    return m_dict;
}

void PopupWindow::timerEvent(QTimerEvent*)
{
    if (lastSelection != QApplication::clipboard()->text(QClipboard::Selection))
    {
        lastSelection = QApplication::clipboard()->text(QClipboard::Selection);
        xSelectionChanged();
    }
}

void PopupWindow::xSelectionChanged()
{
    if (m_modifierKey && ! Keyboard::activeModifiers().testFlag(static_cast<Qt::KeyboardModifier>(m_modifierKey)))
        return ;
    QString m_source = QApplication::clipboard()->text(QClipboard::Selection);
    m_source.remove(QRegExp("^\\W"));
    m_source.remove(QRegExp("\\W.*$"));
    if (m_showIfNotFound || m_dict->isTranslatable(m_source))
    {
        QString translated = m_dict->translate(m_source, true);
        translationView->setHtml(translated);
        translationView->adjustSize();
        move(cursor().pos() - QPoint(30, 30));
        show();
    }
}

*/

