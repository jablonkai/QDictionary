SOURCES += dictionaryreader.cpp \
dictionarytree.cpp \
dictionarywidget.cpp \
mainwindow.cpp \
searchline.cpp \
main.cpp \
settingsdialog.cpp \
kvtmlreader.cpp \
settings.cpp \
dictionary.cpp \
popupwidget.cpp
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
searchline.h \
settingsdialog.h \
kvtmlreader.h \
settings.h \
dictionary.h \
popupwidget.h
FORMS += dictionarywidget.ui \
mainwindow.ui \
settingsdialog.ui
QT += core \
xml \
gui
TRANSLATIONS += translations/qdictionary_hu.ts

OBJECTS_DIR = ../build

UI_DIR = ../build

MOC_DIR = ../build

RCC_DIR = ../build
RESOURCES += qdictionary.qrc

