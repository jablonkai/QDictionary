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
#include "settings.h"

#include <QApplication>
#include <QSettings>


Settings::Settings()
{
    read();
}


Settings::~Settings()
{
    write();
}


void Settings::read()
{
    QSettings settings;

    settings.beginGroup("Translation");
    _automaticTranslation = settings.value("automatic", true).toBool();
    _translation = settings.value("selected", "en").toString();
    settings.endGroup();

    settings.beginGroup("Dictionary");
    _dictDirs = settings.value("dirs", QApplication::instance()->applicationDirPath() + "/dict").toStringList();
    settings.endGroup();
}


void Settings::write()
{
    QSettings settings;

    settings.beginGroup("Translation");
    settings.setValue("automatic", _automaticTranslation);
    settings.setValue("selected", _translation);
    settings.endGroup();

    settings.beginGroup("Dictionary");
    settings.setValue("dirs", _dictDirs);
    settings.endGroup();
}
