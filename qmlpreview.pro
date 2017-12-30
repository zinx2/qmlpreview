#-------------------------------------------------
#
# Project created by QtCreator 2017-11-17T05:28:15
#
#-------------------------------------------------

QT       += core gui quickwidgets sql quick qml quickcontrols2
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qmlpreview
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/binding_listview.cpp \
    src/design.cpp \
    src/dragwidget.cpp \
    src/item_delegate.cpp \
    src/item_model.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/model.cpp \
    src/qml_viewer.cpp \
    src/widget_adjustbar.cpp \
    src/widget_explorer.cpp \
    src/widget_log.cpp \
    src/widget_menubar.cpp \
    src/widget_preview.cpp \
    src/widget_statusbar.cpp \
    src/widget_viewer.cpp \
    src/Option.cpp \
    src/screeninfo.cpp \
    src/screeninfo2.cpp \
    src/display_information.cpp

HEADERS += \
    src/binding_listview.h \
    src/db_manager.h \
    src/design.h \
    src/dragwidget.h \
    src/item_delegate.h \
    src/item_model.h \
    src/mainwindow.h \
    src/model.h \
    src/qheader.h \
    src/qml_viewer.h \
    src/widget_adjustbar.h \
    src/widget_explorer.h \
    src/widget_log.h \
    src/widget_menubar.h \
    src/widget_preview.h \
    src/widget_statusbar.h \
    src/widget_viewer.h \
    src/wrapped_widget.h \
    src/Option.h \
    src/screeninfo.h \
    src/screeninfo2.h \
    src/display_information.h

FORMS += \
     mainwindow.ui \

SUBDIRS += \
    qmlpreview.pro

DISTFILES += \
    qmlpreview.pro.user \

RESOURCES += \
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
