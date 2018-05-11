#-------------------------------------------------
#
# Project created by QtCreator 2018-03-06T11:50:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectAllocation
TEMPLATE = app


SOURCES += main.cpp\
        projectallocationgui.cpp \
    student.cpp \
    project.cpp \
    projectlistmodel.cpp \
    studentlistmodel.cpp \
    DarkStyle.cpp

HEADERS  += projectallocationgui.h \
    student.h \
    project.h \
    projectlistmodel.h \
    studentlistmodel.h \
    DarkStyle.h

FORMS    += projectallocationgui.ui

RESOURCES += \
    darkstyle.qrc
