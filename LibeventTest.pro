TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/ -levent

SOURCES += main.cpp \
    clientone.cpp \
    serverone.cpp \
    clienttwo.cpp \
    servertow.cpp \

HEADERS += \
    clientone.h \
    serverone.h \
    clienttwo.h \
    servertow.h \
