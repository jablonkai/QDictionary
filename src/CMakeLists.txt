PROJECT(QDictionary)

SET(Qt5Core_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Core/)
SET(Qt5Gui_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Gui/)
SET(Qt5Widgets_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Widgets/)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)

# TODO: Remove me once fixed in ECM module
IF(Qt5Core_FOUND)
  # Avoid errors and build in PIC mode:
  # qt5/qtbase/include/QtCore/qglobal.h:1765:4: error:
  #   #error "You must build your code with position independent code if Qt was
  #   built with -reduce-relocations. " "Compile your code with -fPIC or -fPIE."
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ENDIF()

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)
SET(QDictionary_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/)

SET(QDictionary_SRCS
    dictionarydialog.cpp
    dictionarymanager.cpp
    dictionarymodel.cpp
    dictionaryreader.cpp
    dictionarytreewidget.cpp
    dictionarywidget.cpp
    dictionarywriter.cpp
    editwidget.cpp
    entry.cpp
    main.cpp
    mainwindow.cpp
    searchline.cpp
    searchmodel.cpp
    settings.cpp
    settingsdialog.cpp)
SET(QDictionary_MOC_HDRS
    dictionarydialog.h
    dictionarymanager.h
    dictionarymodel.h
#    dictionaryreader.h
    dictionarytreewidget.h
    dictionarywidget.h
#    dictionarywriter.h
    editwidget.h
#   entry.h
    mainwindow.h
    searchline.h
    searchmodel.h
#    settings.h
    settingsdialog.h)
SET(QDictionary_UIS
    dictionarydialog.ui
    dictionarywidget.ui
    editwidget.ui
    mainwindow.ui
    settingsdialog.ui)
SET(QDictionary_RCCS
    qdictionary.qrc)

QT5_WRAP_CPP(QDictionary_MOC_SRCS ${QDictionary_MOC_HDRS})
QT5_WRAP_UI(QDictionary_UIS_H ${QDictionary_UIS})
QT5_ADD_RESOURCES(QDictionary_RCC_SRCS ${QDictionary_RCCS})

ADD_EXECUTABLE(qdictionary
    ${QDictionary_SRCS}
    ${QDictionary_MOC_SRCS}
    ${QDictionary_UIS_H}
    ${QDictionary_RCC_SRCS})
TARGET_LINK_LIBRARIES(qdictionary
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${QDictionary_INCLUDE_DIR})
