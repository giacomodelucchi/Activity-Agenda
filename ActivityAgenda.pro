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
    test/testJsonIO.cpp \
    gui/mainwindow.cpp \
    gui/VistaElencoAttivita.cpp \
    gui/VistaDettaglioAttivita.cpp \
    gui/VistaEditorAttivita.cpp \
    gui/VistaEditorLista.cpp \
    gui/VistaAiuto.cpp

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
    test/testJsonIO.h \
    gui/mainwindow.h \
    gui/VistaElencoAttivita.h \
    gui/VistaDettaglioAttivita.h \
    gui/VistaEditorAttivita.h \
    gui/VistaEditorLista.h \
    gui/VistaAiuto.h

RESOURCES += \
    risorse.qrc
    
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

