TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

unix: {
    DEFINES += PLATFORM_DESKTOP
    LIBS += -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -DPLATFORM_DESKTOP
    INCLUDEPATH += -I/usr/local/include
}

SOURCES += \
        dict.c \
        fx.c \
        main.c \
        menu.c \
        particles.c \
        resources.c

HEADERS += \
    dict.h \
    fx.h \
    main.h \
    menu.h \
    particles.h \
    resources.h
