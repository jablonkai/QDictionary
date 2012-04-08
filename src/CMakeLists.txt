PROJECT(QDictionary)

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
