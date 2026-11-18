QT += core gui widgets

CONFIG += c++17

INCLUDEPATH += $$PWD/src \
               $$PWD/src/core \
               $$PWD/src/models \
               $$PWD/src/ui

HEADERS += \
    src/core/Vector.h \
    src/models/ThueBaoCoDinh.h \
    src/models/ThanhPho.h \
    src/models/QuanLyDanhBa.h \
    src/models/NguoiDung.h \
    src/ui/LoginDialog.h \
    src/ui/RegisterDialog.h \
    src/ui/DanhBaWindow.h

SOURCES += \
    src/main.cpp \
    src/models/ThueBaoCoDinh.cpp \
    src/models/ThanhPho.cpp \
    src/models/QuanLyDanhBa.cpp \
    src/models/NguoiDung.cpp \
    src/ui/LoginDialog.cpp \
    src/ui/RegisterDialog.cpp \
    src/ui/DanhBaWindow.cpp