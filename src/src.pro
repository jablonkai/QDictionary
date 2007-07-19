SOURCES += dictionaryreader.cpp \
dictionarytree.cpp \
dictionarywidget.cpp \
mainwindow.cpp \
searchline.cpp \
main.cpp \
dictionarywriter.cpp \
settingsdialog.cpp \
kvtmlreader.cpp \
editwidget.cpp \
newdialog.cpp \
settings.cpp \
dictionary.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
	  release
TARGET = ../bin/qdictionary

HEADERS += dictionaryreader.h \
dictionarytree.h \
dictionarywidget.h \
mainwindow.h \
version.h \
searchline.h \
dictionarywriter.h \
settingsdialog.h \
kvtmlreader.h \
editwidget.h \
newdialog.h \
settings.h \
dictionary.h
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
