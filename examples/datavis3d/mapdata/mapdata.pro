SOURCES += main.cpp mapdata.cpp
HEADERS += mapdata.h

QT += datavis3d

target.path = $$[QT_INSTALL_EXAMPLES]/datavis3d/mapdata
INSTALLS += target

RESOURCES += \
    mapdata.qrc
