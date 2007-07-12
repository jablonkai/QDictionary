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
newdialog.cpp
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
newdialog.h
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
OBJECTS_DIR = /home/tamas/Projects/qdictionary/build

UI_DIR = /home/tamas/Projects/qdictionary/build

MOC_DIR = /home/tamas/Projects/qdictionary/build

