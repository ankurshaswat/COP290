#-------------------------------------------------
#
# Project created by QtCreator 2018-04-06T12:45:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ED_Project
TEMPLATE = app
QT += uitools

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += include

SOURCES += \
        main.cpp \
        src/mainwindow.cpp \
        optionwindow.cpp \
    src/renderMethods.cpp \
    src/reconstMethods.cpp \
    src/objLoader.cpp \
    src/hiddenLines.cpp \
    src/helperfunctions.cpp \
    src/figures.cpp \
    src/complexcomponents.cpp

HEADERS += \
        optionwindow.h \
        include/mainwindow.h \
    include/structs.h \
    include/renderMethods.h \
    include/reconstMethods.h \
    include/objLoader.h \
    include/hiddenLines.h \
    include/helperfunctions.h \
    include/figures.h \
    include/complexComponents.h \
    include/basicComponents.h

FORMS += \
        optionwindow.ui \
    mainwindow.ui
