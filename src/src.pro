SOURCES += dictionarywidget.cpp \
mainwindow.cpp \
searchline.cpp \
main.cpp \
settingsdialog.cpp \
settings.cpp \
dictionaryreader.cpp \
editwidget.cpp \
dictionarywriter.cpp \
dictionarymanager.cpp \
dictionarymodel.cpp \
 searchmodel.cpp \
 dictionarydialog.cpp \
 entry.cpp \
 dictionarytreewidget.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
	  release
TARGET = ../bin/qdictionary

HEADERS += dictionarywidget.h \
mainwindow.h \
searchline.h \
settingsdialog.h \
settings.h \
dictionaryreader.h \
editwidget.h \
dictionarywriter.h \
dictionarymanager.h \
dictionarymodel.h \
 searchmodel.h \
 dictionarydialog.h \
 entry.h \
 dictionarytreewidget.h
FORMS += dictionarywidget.ui \
mainwindow.ui \
settingsdialog.ui \
editwidget.ui \
dictionarydialog.ui
QT += core \
xml \
gui
TRANSLATIONS += translations/qdictionary_hu.ts

OBJECTS_DIR = ../build

UI_DIR = ../build

MOC_DIR = ../build

RCC_DIR = ../build
RESOURCES += qdictionary.qrc

