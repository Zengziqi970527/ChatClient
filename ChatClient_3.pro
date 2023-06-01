QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#RC_FILE = exeIcon.rc

SOURCES += \
    client.cpp \
    friendlist.cpp \
    main.cpp \
    register.cpp \
    smtp.cpp \
    widget.cpp

HEADERS += \
    client.h \
    friendlist.h \
    register.h \
    smtp.h \
    widget.h

FORMS += \
    client.ui \
    friendlist.ui \
    register.ui \
    widget.ui
#RC_FILE = ChatClient_3.rc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
