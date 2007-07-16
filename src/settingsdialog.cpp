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
#include "settingsdialog.h"

#include <QtGui>

#include "settings.h"


SettingsDialog::SettingsDialog(Settings *s, QWidget *parent) : settings(s), QDialog(parent)
{
    ui.setupUi(this);

    ui.dirListWidget->addItems(settings->dictDirs());

    QPalette palette = ui.firstColorButton->palette();
    palette.setColor(QPalette::Window, settings->firstColor());
    ui.firstColorButton->setPalette(palette);

    palette = ui.secondColorButton->palette();
    palette.setColor(QPalette::Window, settings->secondColor());
    ui.secondColorButton->setPalette(palette);

    connect(ui.addDirButton, SIGNAL(clicked()), this, SLOT(slotAddDir()));
    connect(ui.removeDirButton, SIGNAL(clicked()), this, SLOT(slotRemoveDir()));
    connect(ui.firstColorButton, SIGNAL(clicked()), this, SLOT(slotChangeColor()));
    connect(ui.secondColorButton, SIGNAL(clicked()), this, SLOT(slotChangeColor()));
}


SettingsDialog::~SettingsDialog()
{
}


void SettingsDialog::accept()
{
    settings->dictDirs().clear();
    for (int i = 0; i < ui.dirListWidget->count(); ++i)
        settings->dictDirs().push_back(ui.dirListWidget->item(i)->text());
    settings->setFirstColor(ui.firstColorButton->palette().color(QPalette::Window));
    settings->setSecondColor(ui.secondColorButton->palette().color(QPalette::Window));

    QDialog::accept();
}


void SettingsDialog::slotAddDir()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select dictionaries directory"));
    if (!dirName.isEmpty())
        ui.dirListWidget->addItem(dirName);
}


void SettingsDialog::slotRemoveDir()
{
    ui.dirListWidget->takeItem(ui.dirListWidget->currentRow());
}


void SettingsDialog::slotChangeColor()
{
    QWidget *widget = qobject_cast<QWidget*>(sender());

    QColor color = QColorDialog::getColor(widget->palette().color(QPalette::Window), this);
    if (color.isValid())
    {
        QPalette palette = widget->palette();
        palette.setColor(QPalette::Window, color);
        widget->setPalette(palette);
    }
}
