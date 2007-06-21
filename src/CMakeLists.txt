PROJECT(qdictionary)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)
set(qengineer_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/)

set(qdictionary_SRCS
    aboutdialog.cpp
    dictionary.cpp
    dictionaryreader.cpp
    dictionarytree.cpp
    dictionarywidget.cpp
    editwidget.cpp
    entry.cpp
    main.cpp
    mainwindow.cpp
    searchline.cpp)
set(qdictionary_MOC_HDRS
    aboutdialog.h
    dictionarytree.h
    dictionarywidget.h
    editwidget.h
    mainwindow.h
    searchline.h)
set(qdictionary_UIS
    aboutdialog.ui
    dictionarywidget.ui
    editwidget.ui
    mainwindow.ui)
set(qdictionary_RCCS
    dictionarywidget.qrc
    editwidget.qrc
    mainwindow.qrc)

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
