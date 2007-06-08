SOURCES += main.cpp \
dictionary.cpp \
dictionaryreader.cpp \
dictionarytree.cpp \
dictionarywidget.cpp \
entry.cpp \
lineedit.cpp \
mainwindow.cpp
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
lineedit.h \
mainwindow.h \
version.h
FORMS += dictionarywidget.ui \
mainwindow.ui
QT += core \
xml
