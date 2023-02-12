msvc{
        QMAKE_CFLAGS += /utf-8
        QMAKE_CXXFLAGS += /utf-8
}

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addonesubjectdetail.cpp \
    component/deletebutton.cpp \
    component/numberlineedit.cpp \
    component/paperwidget.cpp \
    config/daoconfig.cpp \
    config/esutil.cpp \
    config/subjectservice.cpp \
    createsubjectwindow.cpp \
    extractpaper.cpp \
    main.cpp \
    mainwindow.cpp \
    pojo/category.cpp \
    pojo/sanswer.cpp \
    pojo/spaper.cpp \
    pojo/spapercategory.cpp \
    pojo/subject.cpp \
    pojo/task.cpp

HEADERS += \
    addonesubjectdetail.h \
    component/deletebutton.h \
    component/numberlineedit.h \
    component/paperwidget.h \
    config/daoconfig.h \
    config/esutil.h \
    config/subjectservice.h \
    createsubjectwindow.h \
    extractpaper.h \
    mainwindow.h \
    pojo/category.h \
    pojo/datastruct.h \
    pojo/sanswer.h \
    pojo/spaper.h \
    pojo/spapercategory.h \
    pojo/subject.h \
    pojo/task.h

FORMS += \
    addonesubjectdetail.ui \
    createsubjectwindow.ui \
    extractpaper.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource/FResourece.qrc
