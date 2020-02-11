CONFIG -= qt
CONFIG += console
TARGET = radshooter

HEADERS = \
    enemy.h \
    enemyhandler.h \
    game.h \
    gameobject.h \
    physics.h \
    player.h \
    timer.h

SOURCES = \
   $$PWD/main.cpp \
   enemy.cpp \
   enemyhandler.cpp \
   game.cpp \
   gameobject.cpp \
   physics.cpp \
   player.cpp \
   timer.cpp

win32 {
    # Windows build config
    LIBDIR = G:/vsdevlib

    INCLUDEPATH =   $$LIBDIR/SDL2_image-2.0.5/include \
                    $$LIBDIR/SDL2-2.0.10/include

    LIBS += -L$$LIBDIR/SDL2_image-2.0.5/lib/x86/ -lSDL2_image
    LIBS += -L$$LIBDIR/SDL2-2.0.10/lib/x86/ -lSDL2main -lSDL2

} else{
    # Linux build config
    INCLUDEPATH += /usr/include/SDL2 \
                   /usr/local/include/SDL2

    LIBS += -Lusr/lib -lSDL2 -lSDL2main
    LIBS += -Lusr/local/lib -lSDL2_image
}

