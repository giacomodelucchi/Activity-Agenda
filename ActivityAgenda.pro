QT = core gui

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        core/gerarchia/attivita.cpp \
        core/gerarchia/evento.cpp \
        core/gerarchia/eventoRicorrente.cpp \
        core/gerarchia/lista.cpp \
        core/gerarchia/voceLista.cpp \
        main.cpp

HEADERS += \
    core/gerarchia/attivita.h \
    core/gerarchia/evento.h \
    core/gerarchia/eventoRicorrente.h \
    core/gerarchia/lista.h \
    core/gerarchia/voceLista.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

