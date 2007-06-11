PROJECT(qdictionary)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)
set(qengineer_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/)

set(qdictionary_SRCS
    dictionary.cpp
    dictionaryreader.cpp
    dictionarytree.cpp
    dictionarywidget.cpp
    entry.cpp
    main.cpp
    mainwindow.cpp
    searchline.cpp)
set(qdictionary_MOC_HDRS
    dictionarytree.h
    dictionarywidget.h
    mainwindow.h
    searchline.h)
set(qdictionary_UIS
    dictionarywidget.ui
    mainwindow.ui)

QT4_WRAP_CPP(qdictionary_MOC_SRCS ${qdictionary_MOC_HDRS})
QT4_WRAP_UI(qdictionary_UIS_H ${qdictionary_UIS})

add_executable(qdictionary
    ${qdictionary_SRCS}
    ${qdictionary_MOC_SRCS} 
    ${qdictionary_UIS_H})
target_link_libraries(qdictionary
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTXML_LIBRARY})
include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
    ${QT_QTXML_INCLUDE_DIR}
    ${qengineer_INCLUDE_DIR})
