SOURCES += dictionaryreader.cpp \
dictionarytree.cpp \
dictionarywidget.cpp \
mainwindow.cpp \
searchline.cpp \
main.cpp \
editwidget.cpp \
dictionarywriter.cpp \
newdialog.cpp \
dictionarymodel.cpp \
settingsdialog.cpp
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
editwidget.h \
dictionarywriter.h \
newdialog.h \
dictionarymodel.h \
settingsdialog.h
FORMS += dictionarywidget.ui \
mainwindow.ui \
editwidget.ui \
newdialog.ui \
settingsdialog.ui
QT += core \
xml \
gui
TRANSLATIONS += translations/qdictionary_hu.ts

RESOURCES += qdictionary.qrc
OBJECTS_DIR = /home/tamas/Projects/qdictionary/build

UI_DIR = /home/tamas/Projects/qdictionary/build

MOC_DIR = /home/tamas/Projects/qdictionary/build

