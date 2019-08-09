TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt
QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
        main.cpp


isEmpty(TARGET_EXT) {
    win32 {
        #TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

CONFIG(release, debug|release):{
     # release
     release: DESTDIR = "release"
     #DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/.executable/$${TARGET}$${TARGET_CUSTOM_EXT}))
     DEPLOY_TARGET = $$shell_quote($$shell_path(/.executable/$${TARGET}$${TARGET_CUSTOM_EXT}))
    MyMakefile = Makefile.Release
 }else:CONFIG(debug, debug|release):{
     # debug
     debug: DESTDIR = "debug"
     #DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/.executable/$${TARGET}$${TARGET_CUSTOM_EXT}))
     DEPLOY_TARGET = $$shell_quote($$shell_path(/.executable/$${TARGET}$${TARGET_CUSTOM_EXT}))
     #DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/$${TARGET}$${TARGET_CUSTOM_EXT}))
     MyMakefile = Makefile.Debug
 }

MYFILE = $$OUT_PWD/$$DESTDIR/".executable"/$$TARGET

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
QMAKE_MAKEFILE = $$DESTDIR/Makefile
MAKEFILE = $$DESTDIR/$$MyMakefile
TARGET = $$DEPLOY_TARGET



HEADERS +=

DISTFILES += \
    README.md


win32: LIBS += -L$$PWD/libs/ -lz
win32: LIBS += -L$$PWD/libs/ -lquazip

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/z.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/libz.a

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/quazip.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/libquazip.a

DEPLOY_COMMAND = windeployqt --qmldir $$PWD
QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${MYFILE}".exe"
