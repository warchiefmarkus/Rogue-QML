TARGET = app
QT += qml quick widgets
CONFIG+= qt plugin
CONFIG += c++11
SOURCES += main.cpp \
    enginePlugin.cpp \
    dungeon.cpp
include(qml-box2d/box2d-static.pri)

INCLUDEPATH += qml-box2d

HEADERS += \
    enginePlugin.h \
    dungeon.h \
    utils.h \
    DungeonGenerator.h

RESOURCES += \
    qml.qrc
