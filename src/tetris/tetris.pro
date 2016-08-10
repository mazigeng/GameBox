QT += core
QT -= gui

TARGET = tetris
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tetrisdata.cpp \
    consolemodem.cpp \
    tetriscell.cpp \
    tetrisdriver.cpp


CONFIG(debug, debug|release) {
DESTDIR += ../binD
} else {
DESTDIR += ../bin
}

HEADERS += \
    tetrisdata.h \
    consolemodem.h \
    tetriscell.h \
    tetrisdriver.h


