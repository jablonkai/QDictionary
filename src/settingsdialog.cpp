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


SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    ui.setupUi(this);

    Settings *settings = Settings::instance();

    ui.dirListWidget->addItems(settings->dictDirs());
    ui.trayIconCheckBox->setChecked(settings->isTrayIconVisible());
    ui.scanCheckBox->setChecked(settings->scan());
    ui.automaticTranslationcheckBox->setChecked(settings->isAutomaticTranslation());

    connect(ui.addDirButton, SIGNAL(clicked()), this, SLOT(slotAddDir()));
    connect(ui.removeDirButton, SIGNAL(clicked()), this, SLOT(slotRemoveDir()));
}


SettingsDialog::~SettingsDialog()
{
}


void SettingsDialog::accept()
{
    Settings *settings = Settings::instance();

    settings->dictDirs().clear();
    for (int i = 0; i < ui.dirListWidget->count(); ++i)
        settings->dictDirs().push_back(ui.dirListWidget->item(i)->text());

    settings->setTrayIconVisible(ui.trayIconCheckBox->checkState());
    settings->setScan(ui.scanCheckBox->checkState());
    settings->setAutomaticTranslation(ui.automaticTranslationcheckBox->checkState());

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
