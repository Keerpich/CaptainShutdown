#-------------------------------------------------
#
# Project created by QtCreator 2012-06-24T12:27:41
#
#-------------------------------------------------

QT       += core gui

TARGET = CptShutWin
TEMPLATE = app
win32:RC_FILE += myapp.rc


SOURCES += main.cpp\
        mainwindow.cpp \
    setpassword.cpp \
    askpassword.cpp \
    note.cpp \
    addnote.cpp \
    focuslineedit.cpp

HEADERS  += mainwindow.h \
    setpassword.h \
    askpassword.h \
    note.h \
    addnote.h \
    focuslineedit.h

FORMS    += \
    mainwindow.ui \
    setpassword.ui \
    askpassword.ui \
    addnote.ui
