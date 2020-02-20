CONFIG -= qt
CONFIG += console
TARGET = radshooter

HEADERS = \
    $$PWD/src/enemy.h \
    $$PWD/src/enemyhandler.h \
    $$PWD/src/game.h \
    $$PWD/src/gameobject.h \
    $$PWD/src/player.h \
    $$PWD/src/ui/textbox.h \
    $$PWD/src/ui/healthui.h \
    $$PWD/src/util/event.h \
    $$PWD/src/util/physics.h \
    $$PWD/src/util/timer.h \
    $$PWD/src/util/observer.h \
    $$PWD/src/util/subject.h

SOURCES = \
   $$PWD/src/main.cpp \
   $$PWD/src/enemy.cpp \
   $$PWD/src/enemyhandler.cpp \
   $$PWD/src/game.cpp \
   $$PWD/src/gameobject.cpp \
   $$PWD/src/player.cpp \
   $$PWD/src/ui/textbox.cpp \
   $$PWD/src/ui/healthui.cpp \
   $$PWD/src/util/physics.cpp \
   $$PWD/src/util/timer.cpp \
   $$PWD/src/util/observer.cpp \
   $$PWD/src/util/subject.cpp

INCLUDEPATH +=  $$PWD/src/ \
                $$PWD/src/util \
                $$PWD/src/ui \

win32 {
    # Windows build config
    LIBDIR = G:/vsdevlib

    INCLUDEPATH +=  $$LIBDIR/SDL2-2.0.10/include \
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
    LIBS += -Lusr/local/lib -lSDL2_image -lSDL2_ttf
}

