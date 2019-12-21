QT += core gui

QT += charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        chart4anything.cpp \
        core/chart_object.cpp \
        core/controller/data_manager.cpp \
        core/global_setting.cpp \
        core/pipline/base_pipline.cpp \
        core/pipline/differential_pipline.cpp \
        core/pipline/integral_pipline.cpp \
        core/pipline/original_pipline.cpp \
        core/view/differential_view.cpp \
        core/view/integral_view.cpp \
        core/view/original_view.cpp \
        core/view/view_center.cpp \
        entity/dataentity.cpp \
        exception/chart_exception.cpp \
        extra/extra_chart_view.cpp \
        main.cpp \
        utils/util.cpp \
        mainwindow.cpp

HEADERS += \
    core/common.h \
    core/controller/data_manager.h \
    core/global_setting.h \
    core/pipline/base_pipline.h \
    core/pipline/differential_pipline.h \
    core/pipline/integral_pipline.h \
    core/pipline/original_pipline.h \
    core/view/differential_view.h \
    core/view/integral_view.h \
    core/view/original_view.h \
    core/view/view_center.h \
    extra/extra_chart_view.h \
    mainwindow.h \
    chart4anything.h \
    core/chart_object.h \
    entity/dataentity.h \
    exception/chart_exception.h \
    utils/util.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
