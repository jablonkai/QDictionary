SOURCES += dictionary.cpp \
dictionaryreader.cpp \
dictionarytree.cpp \
dictionarywidget.cpp \
entry.cpp \
mainwindow.cpp \
searchline.cpp \
main.cpp \
editwidget.cpp \
aboutdialog.cpp \
dictionarywriter.cpp \
newdialog.cpp
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
searchline.h \
editwidget.h \
aboutdialog.h \
dictionarywriter.h \
newdialog.h
FORMS += dictionarywidget.ui \
mainwindow.ui \
editwidget.ui \
aboutdialog.ui \
newdialog.ui
QT += core \
xml \
gui
TRANSLATIONS += translations/qdictionary_hu.ts

RESOURCES += mainwindow.qrc \
editwidget.qrc \
dictionarywidget.qrc
