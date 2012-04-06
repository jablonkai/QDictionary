PROJECT(qdictionary)

#find_package(Qt4 REQUIRED)
set(Qt5Core_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Core/)
set(Qt5Gui_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Gui/)
set(Qt5Widgets_DIR /home/tamas/Downloads/Qt5-alpha/lib/cmake/Qt5Widgets/)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)
set(qdictionary_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/)

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

QT5_WRAP_CPP(qdictionary_MOC_SRCS ${qdictionary_MOC_HDRS})
QT5_WRAP_UI(qdictionary_UIS_H ${qdictionary_UIS})
QT5_ADD_RESOURCES(qdictionary_RCC_SRCS ${qdictionary_RCCS})

add_executable(qdictionary
    ${qdictionary_SRCS}
    ${qdictionary_MOC_SRCS} 
    ${qdictionary_UIS_H}
    ${qdictionary_RCC_SRCS})
target_link_libraries(qdictionary
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES})
include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${qdictionary_INCLUDE_DIR})
