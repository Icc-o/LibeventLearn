TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/ -levent
LIBS += -L/usr/local/lib -lprotobuf -lpthread

INCLUDEPATH += /usr/cc/pugixml/pugixml-master/src

SOURCES += main.cpp \
    clientone.cpp \
    serverone.cpp \
    clienttwo.cpp \
    servertow.cpp \
    configs/Configs.cpp \
    third-party/pugixml.cpp \
    serverthree.cpp \
    configs/basestruct.cpp \
    configs/protos/User.pb.cc \
    clientthree.cpp

HEADERS += \
    clientone.h \
    serverone.h \
    clienttwo.h \
    servertow.h \
    configs/Configs.h \
    third-party/pugixml.hpp \
    third-party/pugiconfig.hpp \
    serverthree.h \
    configs/basestruct.h \
    configs/protos/User.pb.h \
    clientthree.h
