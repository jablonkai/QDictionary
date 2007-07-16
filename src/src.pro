SOURCES += dictionaryreader.cpp \
dictionarytree.cpp \
dictionarywidget.cpp \
mainwindow.cpp \
searchline.cpp \
main.cpp \
dictionarywriter.cpp \
dictionarymodel.cpp \
settingsdialog.cpp \
kvtmlreader.cpp \
editwidget.cpp \
newdialog.cpp \
settings.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/qdictionary

HEADERS += dictionaryreader.h \
dictionarytree.h \
dictionarywidget.h \
mainwindow.h \
version.h \
searchline.h \
dictionarywriter.h \
dictionarymodel.h \
settingsdialog.h \
kvtmlreader.h \
editwidget.h \
newdialog.h \
settings.h
FORMS += dictionarywidget.ui \
mainwindow.ui \
settingsdialog.ui \
editwidget.ui \
newdialog.ui
QT += core \
xml \
gui
TRANSLATIONS += translations/qdictionary_hu.ts

RESOURCES += qdictionary.qrc
OBJECTS_DIR = ../build

UI_DIR = ../build

MOC_DIR = ../build

RCC_DIR = ../build
