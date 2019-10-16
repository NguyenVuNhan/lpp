QT -= gui

TEMPLATE = lib
DEFINES += SRC_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cnf/cnf.cpp \
    logging.cpp \
    notation/and.cpp \
    notation/biimplicate.cpp \
    notation/exists.cpp \
    notation/forall.cpp \
    notation/implicate.cpp \
    notation/multiand.cpp \
    notation/multior.cpp \
    notation/nand.cpp \
    notation/negate.cpp \
    notation/node.cpp \
    notation/or.cpp \
    notation/statement.cpp \
    notation/value.cpp \
    notation/variable.cpp \
    proposition/predicate.cpp \
    proposition/tableaux/semantictableaux.cpp \
    proposition/tableaux/stnode.cpp \
    proposition/tree.cpp \
    table/rows.cpp \
    table/simpletable.cpp \
    table/truthtable.cpp

HEADERS += \
    SemanticTableaux/enum.h \
    Struct/variable.h \
    cnf/cnf.h \
    logging.h \
    notation/and.h \
    notation/biimplicate.h \
    notation/exists.h \
    notation/forall.h \
    notation/implicate.h \
    notation/multiand.h \
    notation/multior.h \
    notation/nand.h \
    notation/negate.h \
    notation/node.h \
    notation/or.h \
    notation/statement.h \
    notation/value.h \
    notation/variable.h \
    proposition/predicate.h \
    proposition/tableaux/enum.h \
    proposition/tableaux/semantictableaux.h \
    proposition/tableaux/stnode.h \
    proposition/tree.h \
    table/rows.h \
    table/simpletable.h \
    table/truthtable.h \
    utils.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
