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

#include <QColor>
#include <QStringList>


class Settings
{
public:
    Settings();
    ~Settings();

    void setDictDirs(const QStringList &stringList) { _dictDirs = stringList; }
    QStringList dictDirs() const { return _dictDirs; }

    void setFirstColor(const QColor &color) { _firstColor = color; }
    QColor firstColor() const { return _firstColor; }
    QString firstColorName() const { return _firstColor.name(); }

    void setSecondColor(const QColor &color) { _secondColor = color; }
    QColor secondColor() const { return _secondColor; }
    QString secondColorName() const { return _secondColor.name(); }

private:
    QStringList _dictDirs;

    QColor _firstColor;
    QColor _secondColor;
};


#endif
