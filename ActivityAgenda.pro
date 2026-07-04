QT = core gui widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    core/gerarchia/attivita.cpp \
    core/gerarchia/evento.cpp \
    core/gerarchia/eventoRicorrente.cpp \
    core/gerarchia/lista.cpp \
    core/gerarchia/voceLista.cpp \
    core/gerarchia/frequenza.cpp \
    core/container/memoria.cpp \
    core/jsonIO/jsonParser.cpp \
    core/jsonIO/jsonIO.cpp \
    gui/mainwindow.cpp \
    gui/VistaElencoAttivita.cpp \
    gui/VistaDettaglioAttivita.cpp \
    gui/VistaEditorAttivita.cpp \
    test/testJsonIO.cpp

HEADERS += \
    core/gerarchia/attivita.h \
    core/gerarchia/evento.h \
    core/gerarchia/eventoRicorrente.h \
    core/gerarchia/lista.h \
    core/gerarchia/voceLista.h \
    core/gerarchia/frequenza.h \
    core/container/memoria.h \
    core/jsonIO/jsonParser.h \
    core/jsonIO/jsonIO.h \
    test/testJsonIO.h

HEADERS += \
    gui/mainwindow.h \
    gui/VistaElencoAttivita.h \
    gui/VistaDettaglioAttivita.h \
    gui/VistaEditorAttivita.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

