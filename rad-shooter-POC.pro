CONFIG -= qt
CONFIG += console
TARGET = radshooter

HEADERS = \
    $$PWD/src/enemy.h \
    $$PWD/src/enemyhandler.h \
    $$PWD/src/game.h \
    $$PWD/src/gameobject.h \
    $$PWD/src/physics.h \
    $$PWD/src/player.h \
    $$PWD/src/timer.h \
    $$PWD/src/textbox.h \
    $$PWD/src/event.h \
    $$PWD/src/healthui.h \
    $$PWD/src/observer.h \
    $$PWD/src/subject.h

SOURCES = \
   $$PWD/src/main.cpp \
   $$PWD/src/enemy.cpp \
   $$PWD/src/enemyhandler.cpp \
   $$PWD/src/game.cpp \
   $$PWD/src/gameobject.cpp \
   $$PWD/src/physics.cpp \
   $$PWD/src/player.cpp \
   $$PWD/src/timer.cpp \
   $$PWD/src/textbox.cpp \
   $$PWD/src/healthui.cpp \
   $$PWD/src/observer.cpp \
   $$PWD/src/subject.cpp

win32 {
    # Windows build config
    LIBDIR = G:/vsdevlib

    INCLUDEPATH =   $$LIBDIR/SDL2-2.0.10/include \
                    $$LIBDIR/SDL2_image-2.0.5/include \
                    $$LIBDIR/SDL2_ttf-2.0.15/include \

    LIBS += -L$$LIBDIR/SDL2-2.0.10/lib/x86/ -lSDL2main -lSDL2
    LIBS += -L$$LIBDIR/SDL2_image-2.0.5/lib/x86/ -lSDL2_image
    LIBS += -L$$LIBDIR/SDL2_ttf-2.0.15/lib/x86/ -lSDL2_ttf

} else{
    # Linux build config
    INCLUDEPATH += /usr/include/SDL2 \
                   /usr/local/include/SDL2

    LIBS += -Lusr/lib -lSDL2 -lSDL2main
    LIBS += -Lusr/local/lib -lSDL2_image
}

