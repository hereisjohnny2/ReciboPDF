QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/cinquilino.cpp \
    ../src/main.cpp \
    ../src/novoinquilinodialog.cpp \
    ../src/recibopdf.cpp

HEADERS += \
    ../src/cinquilino.h \
    ../src/novoinquilinodialog.h \
    ../src/recibopdf.h

FORMS += \
    ../src/novoinquilinodialog.ui \
    ../src/recibopdf.ui

DISTFILES += \
    ../data/inquilinos.json

DESTDIR = ./

OBJECTS_DIR = objects
