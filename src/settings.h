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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QStringList>


class Settings
{
public:
    static Settings *instance() { static Settings instance; return &instance; }

    void setDictDirs(const QStringList &list) { _dictDirs = list; }
    QStringList& dictDirs() { return _dictDirs; }

    void setTrayIconVisible(bool b) { _trayIconVisible = b; }
    bool isTrayIconVisible() { return _trayIconVisible; }

    void setScan(bool b) { _scan = b; }
    bool scan() { return _scan; }

    void setAutomaticTranslation(bool b) { _automaticTranslation = b; }
    bool isAutomaticTranslation() { return _automaticTranslation; }

    void setTranslation(const QString &s) { _translation = s; }
    QString translation() const { return _translation; }

private:
    Settings();
    ~Settings();

    void write();
    void read();

    QStringList _dictDirs;
    bool _trayIconVisible;
    bool _scan;
    bool _automaticTranslation;
    QString _translation;
};


#endif
