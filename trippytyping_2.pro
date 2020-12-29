TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

unix: {
    LIBS += -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -DPLATFORM_DESKTOP
    INCLUDEPATH += -I/usr/local/include
}

SOURCES += \
        dict.c \
        main.c \
        particles.c \
        resources.c

HEADERS += \
    dict.h \
    particles.h \
    resources.h
