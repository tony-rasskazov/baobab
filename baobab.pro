QT += xml

CONFIG += c++11

folder_01.source = qml/baobab
folder_01.target = qml

DEPLOYMENTFOLDERS = folder_01

SOURCES += main.cpp \
    model.cpp \
    treeitem.cpp \
    persist.cpp


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
#include(deployment.pri)

include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    model.h \
    treeitem.h \
    persist.h

RESOURCES += \
    images.qrc \
    qml.qrc

DISTFILES += \
    qml/baobab/MindNodeView.qml
