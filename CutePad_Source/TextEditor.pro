#-------------------------------------------------
# Originally created by,Thusitha Manathunga, 2012
# Faculty of Engineering, University of Ruhuna.
# ############################################
# This was originally built on Qt 4.8.2
# ============================================
# A work of Serandibsoft, Sri Lanka
# ############################################

QT       += core gui network

TARGET = CutePad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addlink.cpp \
    addtable.cpp \
    savemodifications.cpp \
    dark.cpp \
    settings.cpp \
    checkupdates.cpp \
    updater.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    addlink.h \
    addtable.h \
    savemodifications.h \
    dark.h \
    settings.h \
    checkupdates.h \
    updater.h \
    about.h

FORMS    += mainwindow.ui \
    addlink.ui \
    addtable.ui \
    savemodifications.ui \
    dark.ui \
    settings.ui \
    updater.ui \
    about.ui

RESOURCES += \
    Resources.qrc
RC_FILE = Cute.rc
