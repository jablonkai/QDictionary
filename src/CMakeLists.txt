PROJECT(qdictionary)

#find_package(Qt4 REQUIRED)
set(Qt5Widgets_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Widgets)
find_package(Qt5Widgets REQUIRED)
include(${QT_USE_FILE})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)
set(qengineer_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/)

set(qdictionary_SRCS
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
set(qdictionary_MOC_HDRS
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
set(qdictionary_UIS
    dictionarydialog.ui
    dictionarywidget.ui
    editwidget.ui
    mainwindow.ui
    settingsdialog.ui)
set(qdictionary_RCCS
    qdictionary.qrc)

QT4_WRAP_CPP(qdictionary_MOC_SRCS ${qdictionary_MOC_HDRS})
QT4_WRAP_UI(qdictionary_UIS_H ${qdictionary_UIS})
QT4_ADD_RESOURCES(qdictionary_RCC_SRCS ${qdictionary_RCCS})

add_executable(qdictionary
    ${qdictionary_SRCS}
    ${qdictionary_MOC_SRCS} 
    ${qdictionary_UIS_H}
    ${qdictionary_RCC_SRCS})
target_link_libraries(qdictionary
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTXML_LIBRARY})
include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
    ${QT_QTXML_INCLUDE_DIR}
    ${qengineer_INCLUDE_DIR})
