QT       += core gui

QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #associationcontactinteraction.cpp \
    contact.cpp \
    date.cpp \
    fenetreajoutcontact.cpp \
    fenetreajoutevenement.cpp \
    fenetrecontact.cpp \
    fenetreprincipalecontact.cpp \
    gestioncontact.cpp \
    gestioninteraction.cpp \
    gestiontodo.cpp \
    #initBDD.cpp \
    interaction.cpp \
    main.cpp \
    todo.cpp

HEADERS += \
    #associationcontactinteraction.h \
    contact.h \
    date.h \
    fenetreajoutcontact.h \
    fenetreajoutevenement.h \
    fenetrecontact.h \
    fenetreprincipalecontact.h \
    gestioncontact.h \
    gestioninteraction.h \
    gestiontodo.h \
    interaction.h \
    todo.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
