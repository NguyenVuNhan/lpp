include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../src/SemanticTableaux/enum.h \
        ../src/cnf/cnf.h \
        ../src/logic_manager.h \
        ../src/notation/and.h \
        ../src/notation/biimplicate.h \
        ../src/notation/exists.h \
        ../src/notation/forall.h \
        ../src/notation/implicate.h \
        ../src/notation/multiand.h \
        ../src/notation/multior.h \
        ../src/notation/nand.h \
        ../src/notation/negate.h \
        ../src/notation/node.h \
        ../src/notation/or.h \
        ../src/notation/statement.h \
        ../src/notation/value.h \
        ../src/notation/variable.h \
        ../src/proposition/predicate.h \
        ../src/proposition/tableaux/enum.h \
        ../src/proposition/tableaux/semantictableaux.h \
        ../src/proposition/tableaux/stnode.h \
        ../src/proposition/tree.h \
        ../src/table/rows.h \
        ../src/table/simpletable.h \
        ../src/table/truthtable.h \
        ../src/utils.h \
        test_cnf.h \
        test_logic_manager.h \
        test_notation.h \
        test_predicate.h \
        test_table.h \
        test_tree.h

SOURCES += \
        ../src/cnf/cnf.cpp \
        ../src/logic_manager.cpp \
        ../src/notation/and.cpp \
        ../src/notation/biimplicate.cpp \
        ../src/notation/exists.cpp \
        ../src/notation/forall.cpp \
        ../src/notation/implicate.cpp \
        ../src/notation/multiand.cpp \
        ../src/notation/multior.cpp \
        ../src/notation/nand.cpp \
        ../src/notation/negate.cpp \
        ../src/notation/node.cpp \
        ../src/notation/or.cpp \
        ../src/notation/statement.cpp \
        ../src/notation/value.cpp \
        ../src/notation/variable.cpp \
        ../src/proposition/predicate.cpp \
        ../src/proposition/tableaux/semantictableaux.cpp \
        ../src/proposition/tableaux/stnode.cpp \
        ../src/proposition/tree.cpp \
        ../src/table/rows.cpp \
        ../src/table/simpletable.cpp \
        ../src/table/truthtable.cpp \
        main.cpp
