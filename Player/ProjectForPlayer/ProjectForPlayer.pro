QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    application.cpp \
    personages.cpp \
    player.cpp

HEADERS += \
    application.h \
    personages.h \
    player.h

INCLUDEPATH += D:\Programming\Luffy-s-Adventures\Luffy-s-Adventures\SFML\SFML-2.5.1\include
DEPENDPATH += D:\Programming\Luffy-s-Adventures\Luffy-s-Adventures\SFML\SFML-2.5.1\include

LIBS += -LD:\Programming\Luffy-s-Adventures\Luffy-s-Adventures\SFML\LIBS\

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-system-d -lsfml-network-d -lsfml-main-d -lsfml-window-d -lsfml-graphics-d
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-system -lsfml-network -lsfml-main -lsfml-window -lsfml-graphics


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
