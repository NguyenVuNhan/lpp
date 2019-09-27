#-------------------------------------------------
#
# Project created by QtCreator 2019-04-18T13:24:09
#
#-------------------------------------------------

QT       -= gui

TARGET = LogicLib
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cnf/cnf.cpp \
    logic_manager.cpp \
    notation/and.cpp \
    notation/biimplicate.cpp \
    notation/implicate.cpp \
    notation/multiand.cpp \
    notation/multior.cpp \
    notation/negate.cpp \
    notation/node.cpp \
    notation/or.cpp \
    notation/value.cpp \
    notation/variable.cpp \
    notation/nand.cpp \
    notation/statement.cpp \
    notation/forall.cpp \
    notation/exists.cpp \
    proposition/predicate.cpp \
    proposition/tableaux/semantictableaux.cpp \
    proposition/tableaux/stnode.cpp \
    proposition/tree.cpp \
    table/rows.cpp \
    table/simpletable.cpp \
    table/truthtable.cpp

HEADERS += \
    cnf/cnf.h \
    logic_manager.h \
    notation/biimplicate.h \
    notation/implicate.h \
    notation/multiand.h \
    notation/multior.h \
    notation/negate.h \
    notation/value.h \
    notation/and.h \
    notation/node.h \
    notation/or.h \
    notation/variable.h \
    notation/nand.h \
    notation/statement.h \
    notation/forall.h \
    notation/exists.h \
    proposition/predicate.h \
    proposition/tableaux/enum.h \
    proposition/tableaux/semantictableaux.h \
    proposition/tableaux/stnode.h \
    proposition/tree.h \
    table/rows.h \
    table/simpletable.h \
    table/truthtable.h \
    utils.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
