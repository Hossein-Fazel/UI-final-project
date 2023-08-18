QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Anonymous_User.cpp \
    Base_User.cpp \
    Display_Class.cpp \
    Mention_class.cpp \
    Organisation_User.cpp \
    Tweet_Class.cpp \
    Twitterak_Class.cpp \
    User_Class.cpp \
    login.cpp \
    main.cpp \
    main_profile.cpp \
    mainwindow.cpp \
    others_profile.cpp \
    signup.cpp

HEADERS += \
    Anonymous_User.hpp \
    Base_User.hpp \
    Display_Class.hpp \
    Mention_class.hpp \
    Organisation_User.hpp \
    Tweet_Class.hpp \
    Twitterak_Class.hpp \
    User_Class.hpp \
    login.h \
    main_profile.h \
    mainwindow.h \
    others_profile.h \
    signup.h

FORMS += \
    login.ui \
    main_profile.ui \
    mainwindow.ui \
    others_profile.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target