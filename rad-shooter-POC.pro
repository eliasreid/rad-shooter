CONFIG -= qt
CONFIG += console
TARGET = radshooter

HEADERS = \
    enemy.h \
    enemyhandler.h \
    game.h \
    gameobject.h \
    physics.h \
    player.h

SOURCES = \
   $$PWD/main.cpp \
   enemy.cpp \
   enemyhandler.cpp \
   game.cpp \
   gameobject.cpp \
   physics.cpp \
   player.cpp

# do an if linux / windows for the vsdevlib

LIBDIR = G:/vsdevlib

INCLUDEPATH =   $$LIBDIR/SDL2_image-2.0.5/include \
                $$LIBDIR/SDL2-2.0.10/include

LIBS += -L$$LIBDIR/SDL2_image-2.0.5/lib/x86/ -lSDL2_image
LIBS += -L$$LIBDIR/SDL2-2.0.10/lib/x86/ -lSDL2main -lSDL2
