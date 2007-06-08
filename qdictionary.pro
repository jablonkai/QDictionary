TEMPLATE =   app
DESTDIR +=   ./bin
MOC_DIR +=   ./build/moc
OBJECTS_DIR +=   ./build/o
SOURCES +=   src/main.cpp \
  src/mainwindow.cpp \
  src/dictionary.cpp \
  src/dictionarywidget.cpp \
  src/dictionarytree.cpp \
  src/dictionaryreader.cpp \
  src/entry.cpp \
  src/lineedit.cpp
HEADERS +=   src/mainwindow.h \
  src/dictionary.h \
  src/dictionarywidget.h \
  src/dictionarytree.h \
  src/version.h \
  src/dictionaryreader.h \
  src/entry.h \
  src/lineedit.h
QT +=   gui \
  core \
  xml
UI_DIR +=   ./build/ui
FORMS +=   src/ui/dictionarywidget.ui \
  src/ui/mainwindow.ui
RCC_DIR +=   ./build/rc
INCLUDEPATH +=   ./src
CONFIG +=   release
