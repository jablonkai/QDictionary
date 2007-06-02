TEMPLATE =   app
DESTDIR +=   ./bin
MOC_DIR +=   ./build/moc
OBJECTS_DIR +=   ./build/o
SOURCES +=   src/main.cpp \
  src/mainwindow.cpp \
  src/dictionary.cpp \
  src/dictionarywidget.cpp \
  src/dictionarytree.cpp \
  src/word.cpp \
  src/dictionaryreader.cpp
HEADERS +=   src/mainwindow.h \
  src/dictionary.h \
  src/dictionarywidget.h \
  src/dictionarytree.h \
  src/version.h \
  src/word.h \
  src/dictionaryreader.h
QT +=   gui \
  core \
  xml
UI_DIR +=   ./build/ui
FORMS +=   src/ui/dictionarywidget.ui \
  src/ui/mainwindow.ui
RESOURCES +=   src/resources/mainwindow.qrc \
  src/resources/dictionarywidget.qrc
RCC_DIR +=   ./build/rc
INCLUDEPATH +=   ./src
CONFIG +=   release
TRANSLATIONS +=   qdictionary_hu.ts
