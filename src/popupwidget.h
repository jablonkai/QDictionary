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
class Dictionary;


class PopupWidget : public QWidget
{
    Q_OBJECT

public:
    PopupWidget(QWidget *parent = 0);
    ~PopupWidget();

public slots:
    void slotSetDictionary(Dictionary*);
    void slotScan(bool);

protected:
    void timerEvent(QTimerEvent*);

private:
    void search();

    Dictionary *dict;
    QTextBrowser *textBrowser;
    QString prevSelection;
    int timerId;
};/*#include <QWidget>

class QAction;
class QEvent;
class QTextBrowser;
class QTimer;
class QClipboard;

class DictCore;

class PopupWindow: public QWidget
{
        Q_OBJECT

    public:
        PopupWindow(DictCore *dict = NULL, QWidget *parent = 0);
        ~PopupWindow();

        bool isScan() const;
        int modifierKey() const;
        bool showIfNotFound() const;

        DictCore* dict() const;

    public slots:
        void setScan(bool scan);
        void setModifierKey(int key);
        void setShowIfNotFound(bool mode);

    signals:
        void scanChanged(bool);

    protected:
        void enterEvent(QEvent*);
        void leaveEvent(QEvent*);
        void timerEvent(QTimerEvent*);

    private slots:
        void xSelectionChanged();

    private:
        QTextBrowser *translationView;
        QTimer *closeTimer;
        DictCore* m_dict;
        QString m_source;
        bool m_scan;
        int m_modifierKey;
        bool m_showIfNotFound;
        QString lastSelection;
        int timerId;
};*/
/*class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget();

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *e);

private slots:
    void showIcon(bool s);
private:
    QSvgRenderer *renderer;
    QPixmap       cache;
    QPixmap       icon;
    bool          dirty;
    bool          iconShown;
    QCheckBox    *cbox;
};*/

#endif
