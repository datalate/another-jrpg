#-------------------------------------------------
#
# Project created by QtCreator 2018-08-02T00:07:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = level-editor
TEMPLATE = app

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    $$PWD/../src/tilemanager.cc \
    main.cc \
    mainwindow.cc \
    tileitem.cc \
    editorscene.cc \
    tileselectorscene.cc \
    tileselectorview.cc

HEADERS += \
    $$PWD/../src/types.hh \
    $$PWD/../src/yamlparser.hh \
    $$PWD/../src/tilemanager.hh \
    mainwindow.hh \
    tileitem.hh \
    editorscene.hh \
    tileselectorscene.hh \
    common.hh \
    tileselectorview.hh

FORMS += \
    mainwindow.ui

unix:!macx: LIBS += -L/usr/lib/ -lyaml-cpp

INCLUDEPATH += $$PWD/../3rdparty/yaml-cpp/include
DEPENDPATH += $$PWD/../3rdparty/yaml-cpp/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdparty/yaml-cpp/lib/x64/ -llibyaml-cppmd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdparty/yaml-cpp/lib/x64/ -llibyaml-cppmdd

win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/yaml-cpp/lib/x64/libyaml-cppmd.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../3rdparty/yaml-cpp/lib/x64/libyaml-cppmdd.lib
