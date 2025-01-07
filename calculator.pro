QT += qml scxml quick
QT += testlib

CONFIG += c++11
CONFIG += qmltypes

SOURCES += \
    calculator.cpp
    calculator_qml_resources.cpp \
    ...

HEADERS += calculator-qml.h

QML_IMPORT_NAME = Calculator
QML_IMPORT_MAJOR_VERSION = 1.0

qml_resources.files = \
    qmldir \
    MainWindow.qml \
    Button.qml \
    qrc_qml_resources.cpp

qml_resources.prefix = /qt/qml/Calculator

RESOURCES += qmake_qml_resources.qrc

STATECHARTS = statemachine.scxml

# install
target.path = $$[QT_INSTALL_EXAMPLES]/scxml/calculator
INSTALLS += target
