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
        timerId = startTimer(500);
    }
    else
        killTimer(timerId);
}


void PopupWidget::timerEvent(QTimerEvent*)
{
    QString selection = qApp->clipboard()->text(QClipboard::Selection);
    if (prevSelection != selection)
    {
        prevSelection = selection;
        search();
//        emit changed(m_lastState);
    }
}


void PopupWidget::search()
{
    if (!dict)
        return;
  /*  DictionaryWidget *w = new DictionaryWidget(this);
    w->activateDictionary(dict);
*/
    textBrowser->setHtml(dict->popupSearch(prevSelection));
    textBrowser->adjustSize();
    move(cursor().pos());// - QPoint(30, 30));
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
    closeTimer = new QTimer(this);
    connect(closeTimer, SIGNAL(timeout()), SLOT(close()));
    connect(closeTimer, SIGNAL(timeout()), closeTimer, SLOT(stop()));
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

void PopupWindow::enterEvent(QEvent*)
{
    closeTimer->stop();
}

void PopupWindow::leaveEvent(QEvent*)
{
    closeTimer->start(200);
}*/

/*#include <QSvgRenderer>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QCheckBox>

Widget::Widget()
    : QWidget(0, Qt::FramelessWindowHint),
      icon("internet.png"),
      dirty(true),
      iconShown(false)
{
    //To optimize painting a bit you can set the following:
    //   note that child widgets might not be composed
    //   correctly then though
    //setAttribute(Qt::WA_PaintOnScreen);
    //setAttribute(Qt::WA_NoSystemBackground);

    renderer = new QSvgRenderer(QLatin1String("hummingbird.svg"),
                                this);
    cbox = new QCheckBox(QLatin1String("Show icon"),
                         this);
    cbox->setGeometry(150, 230, 100, 20);
    cbox->setChecked(iconShown);
    connect(cbox, SIGNAL(toggled(bool)),
            this, SLOT(showIcon(bool)));
}


void Widget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setClipRect(e->rect());

    //make sure you clean your widget with a transparent
    //  color before doing any rendering
    //  note the usage of a composition mode Source
    //  it's important!
    p.save();
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.fillRect(rect(), Qt::transparent);
    p.restore();

    if (dirty) {
        cache.fill(Qt::transparent);
        QPainter p(&cache);
        p.setRenderHint(QPainter::Antialiasing);
        renderer->render(&p);
        p.end();
        dirty = false;
    }
    p.drawPixmap(0, 0, cache);
    if (iconShown) {
        p.drawPixmap(20, 20, icon);
    }

}

void Widget::resizeEvent(QResizeEvent *e)
{
    if (e->size() != cache.size()) {
        cache = QPixmap(e->size());
        dirty = true;
        int w = e->size().width();
        int h = e->size().height();
        cbox->setGeometry(w/2 - 50,
                          h - 70,
                          100, 20);
    }
}

void Widget::showIcon(bool s)
{
    if (iconShown != s) {
        iconShown = s;
        update();
    }
}*/
