#include <QApplication>
#include <QQuickView>
#include "box2dplugin.h"
#include "enginePlugin.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Box2DPlugin plugin;
    plugin.registerTypes("Box2D");

    QQuickView viewer;
    viewer.engine()->addImportPath("modules");
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl("qrc:/qml/ANGSC1/main.qml"));
    viewer.show();

    EnginePlugin engine;
    engine.registerTypes("Engine");

    return app.exec();
}
