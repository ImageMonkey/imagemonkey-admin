QT += qml quick quickcontrols2

android{
    Qt += androidextras
}

#LOCAL, TEST, PRODUCTION
_EXECUTIONTARGET_ = "PRODUCTION"

QT_executiontarget = "$${LITERAL_HASH}ifndef __EXECUTIONTARGET__H__"
QT_executiontarget += "$${LITERAL_HASH}define __EXECUTIONTARGET__H__"
QT_executiontarget += "$${LITERAL_HASH}define EXECUTIONTARGET ExcecutionTarget::$$_EXECUTIONTARGET_"
QT_executiontarget += "$${LITERAL_HASH}endif"
write_file($$PWD/source/cpp/executiontarget.h, QT_executiontarget)

include (./ext/quicknative/quicknative.pri)

CONFIG += c++11
CONFIG += resources_big #otherwise compiling failes with "compiler is out of heap space"
CONFIG += qtquickcompiler

SOURCES += \
    source/cpp/main.cpp \
    source/cpp/rest/httpsrequestworker.cpp \
    source/cpp/rest/settings.cpp \
    source/cpp/misc/uid.cpp \
    source/cpp/rest/requests/sslrequest.cpp \
    source/cpp/rest/requests/imagerequest.cpp \
    source/cpp/rest/requests/basicrequest.cpp \
    source/cpp/rest/requests/clientauthrequest.cpp \
    source/cpp/misc/network.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

INCLUDEPATH += .

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    source/cpp/rest/httpsrequestworker.h \
    source/cpp/rest/settings.h \
    source/cpp/misc/uid.h \
    source/cpp/executiontarget.h \
    source/cpp/executiontargetdef.h \
    source/cpp/main.h \
    source/cpp/rest/requests/sslrequest.h \
    source/cpp/rest/requests/imagerequest.h \
    source/cpp/rest/requests/basicrequest.h \
    source/cpp/misc/secrets.h \
    source/cpp/rest/requests/clientauthrequest.h \
    source/cpp/misc/network.h

android{
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    ANDROID_JAVA_SOURCES.path = /src/com/imagesquirrel/imagesquirrel
    ANDROID_JAVA_SOURCES.files = $$files($$PWD/source/java/*.java)
    INSTALLS += ANDROID_JAVA_SOURCES
}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/ext/libraries/android/openssl/openssl1.0.2j/libcrypto.so \
        $$PWD/ext/libraries/android/openssl/openssl1.0.2j/libssl.so
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat
