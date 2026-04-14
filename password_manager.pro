# ============================================================
#  Haseeb Zahid Password Manager
#  Developed by Haseeb Zahid
#  Project file: password_manager.pro  (qmake)
# ============================================================

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++17

TARGET   = PasswordManager
TEMPLATE = app

SOURCES += \
    main.cpp \
    encryption.cpp \
    password_manager.cpp \
    file_handler.cpp \
    login_dialog.cpp \
    add_password_dialog.cpp \
    main_window.cpp

HEADERS += \
    encryption.h \
    password_manager.h \
    file_handler.h \
    login_dialog.h \
    add_password_dialog.h \
    main_window.h

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
