QT += core
QT -= gui

TARGET = tetris
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp


CONFIG(debug, debug|release) {
DESTDIR += ../binD
} else {
DESTDIR += ../bin
}


