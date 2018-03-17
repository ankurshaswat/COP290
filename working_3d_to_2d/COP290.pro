#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T21:00:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = COP290
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
INCLUDEPATH += include/module1

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
    src/objLoader.cpp \
    src/figures.cpp \
    src/renderMethods.cpp \
    optionwindow.cpp \
    src/hiddenLines.cpp \

HEADERS += \
        include/module1/mainwindow.h \
    include/module1/objLoader.h \
    include/module1/basicComponents.h \
    include/module1/figures.h \
    include/module1/renderMethods.h \
    optionwindow.h \
    include/module1/hiddenLines.h \
    include/module1/complexComponents.h \
    include/module1/structs.h \
    include/module1/reconstMethods.h \

FORMS += \
        mainwindow.ui \
    optionwindow.ui
