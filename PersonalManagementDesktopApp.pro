#-------------------------------------------------
#
# Project created by QtCreator 2017-01-08T13:04:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PersonalManagementDesktopApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hourlycompensationemployee.cpp \
    monthlypaidemployee.cpp \
    personnel.cpp \
    salesman.cpp \
    addEmployeeDialog.cpp

HEADERS  += mainwindow.h \
    hourlycompensationemployee.h \
    monthlypaidemployee.h \
    personnel.h \
    salesman.h \
    addEmployeeDialog.h

FORMS    += mainwindow.ui \
    addemployeedialog.ui


win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/' -lucrt
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/' -lucrtd

INCLUDEPATH += 'C:/Program Files (x86)/Windows Kits/10/Include/10.0.10150.0/ucrt'
DEPENDPATH += 'C:/Program Files (x86)/Windows Kits/10/Include/10.0.10150.0/ucrt'

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += 'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/libucrt.a'
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += 'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/libucrtd.a'
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += 'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/ucrt.lib'
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += 'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64/ucrtd.lib'
