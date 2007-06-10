SOURCES += dictionary.cpp \
dictionaryreader.cpp \
dictionarytree.cpp \
dictionarywidget.cpp \
entry.cpp \
mainwindow.cpp \
searchline.cpp \
main.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/qdictionary

HEADERS += dictionary.h \
dictionaryreader.h \
dictionarytree.h \
dictionarywidget.h \
entry.h \
mainwindow.h \
version.h \
searchline.h
FORMS += dictionarywidget.ui \
mainwindow.ui
QT += core \
xml \
gui
TRANSLATIONS += translations/qdictionary_hu.ts

