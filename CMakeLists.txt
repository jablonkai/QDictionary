PROJECT(QDictionary)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

SET(QDICTIONARY_VERSION_MAJOR 0)
SET(QDICTIONARY_VERSION_MINOR 3)
SET(QDICTIONARY_VERSION_PATCH 0)
SET(QDICTIONARY_VERSION ${QDICTIONARY_VERSION_MAJOR}.${QDICTIONARY_VERSION_MINOR}.${QDICTIONARY_VERSION_PATCH})
SET(QDICTIONARY_VERSION_STRING "${QDICTIONARY_VERSION}")

# correct those
SET(Qt5Core_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Core/)
SET(Qt5Gui_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Gui/)
SET(Qt5Widgets_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Widgets/)

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)

# qt5/qtbase/include/QtCore/qglobal.h:1765:4: error:
#   #error "You must build your code with position independent code if Qt was
#   built with -reduce-relocations. " "Compile your code with -fPIC or -fPIE."
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

ADD_SUBDIRECTORY(src)
