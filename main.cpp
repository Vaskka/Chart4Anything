#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>

#include <QList>
#include <QDebug>
#include <QLineSeries>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //

    //
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    QList<QObject*> list = engine.rootObjects();
    for (QObject* obj : list) {
        qDebug() << obj->property("objectName").toString();
    }

    qmlRegisterType<QtCharts::QLineSeries>();

    return app.exec();
}
