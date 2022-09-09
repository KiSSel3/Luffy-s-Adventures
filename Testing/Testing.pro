QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bullet.cpp \
    application.cpp \
    enemy.cpp \
    main.cpp \
    mainmenu.cpp \
    map.cpp \
    pausemenu.cpp \
    personages.cpp \
    player.cpp \
    styleformenu.cpp \
    tinyxml2.cpp


HEADERS += \
    Bullet.h \
    application.h \
    enemy.h \
    mainmenu.h \
    map.h \
    pausemenu.h \
    personages.h \
    player.h \
    styleformenu.h \
    tinyxml2.h

INCLUDEPATH += $$PWD/SFML/include
DEPENDPATH += $$PWD/SFML/include

LIBS += -L$$PWD/SFML/lib/

CONFIG(release, debug|release): LIBS += -L$$PWD/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML/lib/ -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainmenu.ui \
    pausemenu.ui

RESOURCES +=
