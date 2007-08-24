SOURCES += dictionarytree.cpp \
dictionarywidget.cpp \
mainwindow.cpp \
searchline.cpp \
main.cpp \
settingsdialog.cpp \
dictionary.cpp \
popupwidget.cpp \
settings.cpp \
dictionaryreader.cpp \
editwidget.cpp \
newdictionarydialog.cpp \
dictionarywriter.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
	  release
TARGET = ../bin/qdictionary

HEADERS += dictionarytree.h \
dictionarywidget.h \
mainwindow.h \
searchline.h \
settingsdialog.h \
dictionary.h \
popupwidget.h \
settings.h \
dictionaryreader.h \
editwidget.h \
newdictionarydialog.h \
dictionarywriter.h
FORMS += dictionarywidget.ui \
mainwindow.ui \
settingsdialog.ui \
editwidget.ui \
newdictionarydialog.ui
QT += core \
xml \
gui
TRANSLATIONS += translations/qdictionary_hu.ts

OBJECTS_DIR = ../build

UI_DIR = ../build

MOC_DIR = ../build

RCC_DIR = ../build
RESOURCES += qdictionary.qrc

