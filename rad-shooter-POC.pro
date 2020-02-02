CONFIG -= qt
TARGET = radshooter

HEADERS =

SOURCES = \
   $$PWD/main.cpp

# do an if linux / windows for the vsdevlib

LIBDIR = G:/vsdevlib

INCLUDEPATH =   $$LIBDIR/SDL2_image-2.0.5/include \
                $$LIBDIR/SDL2-2.0.10/include

LIBS += -L$$LIBDIR/SDL2_image-2.0.5/lib/x86/ -lSDL2_image
LIBS += -L$$LIBDIR/SDL2-2.0.10/lib/x86/ -lSDL2main -lSDL2
