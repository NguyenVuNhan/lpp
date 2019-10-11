#QT += core
QT -= gui

#TARGET = logic

CONFIG += c++11 console
CONFIG -= app_bundle
#CONFIG += no_keywords

#TEMPLATE = app

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
    main.cpp

DEFINES += BOOST_LOG_DYN_LINK

#INCLUDEPATH += /usr/include/python3.6m
INCLUDEPATH += /usr/include/boost

#LIBS += -L/usr/lib/python3.6m/config -lpython3.6m
LIBS += -L/usr/lib/boost
LIBS += -pthread -lboost_system -lboost_filesystem -lboost_log_setup -lboost_log -lboost_date_time -lboost_thread

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lsrc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lsrc
else:unix: LIBS += -L$$OUT_PWD/../src/ -lsrc

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src
