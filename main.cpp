#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qtquick2applicationviewer.h"

#include "model.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Model m;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("programmModel", &m);
    engine.load(QUrl(QStringLiteral("qrc:/qml/baobab/main.qml")));

    return app.exec();

}
