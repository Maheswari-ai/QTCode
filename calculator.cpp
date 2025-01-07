// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QDebug>
#include <QQmlError>
#include <QFile>

// Declare MyClass for checking file existence
class MyClass {
public:
    void checkFile();
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Connect to the warnings signal for error reporting
    QObject::connect(&engine, &QQmlApplicationEngine::warnings,
                     [](const QList<QQmlError> &warnings) {
                         for (const auto &warning : warnings) {
                             qWarning() << warning.toString();
                         }
                     });

    // Check if the MainWindow.qml file exists
    MyClass myClass;
    myClass.checkFile();

    // Load the main QML file from the resource path
    qDebug() << "Loading QML from qrc:/qml/MainWindow.qml";
    engine.load(QUrl::fromLocalFile("/home/ubuntu/project/qml/MainWindow.qml"));

    // Exit if the root objects are empty (indicating a loading failure)
    if (engine.rootObjects().isEmpty()) {
            qCritical() << "Failed to load QML file!";
    	    return -1;
    }

    return app.exec();
}

// Define the checkFile method of MyClass
void MyClass::checkFile() {
    QFile file(":/qml/MainWindow.qml"); // Ensure the resource path is correct
    if (!file.exists()) {
        qDebug() << "MainWindow.qml not found in resources!";
    } else {
        qDebug() << "MainWindow.qml exists in resources.";	    
    }
}

