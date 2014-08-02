#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QMetaType>
#include <QtTest/qtestcase.h>

#include "treeviewmodel.hpp"
#include "confignode.hpp"
#include "undomanager.hpp"
#include "modeltest/modeltest.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    qRegisterMetaType<TreeViewModel> ("TreeViewModel");
    qRegisterMetaType<ConfigNode> ("ConfigNode");
    qRegisterMetaType<UndoManager> ("UndoManager");

    QString locale = QLocale::system().name();

    QTranslator tr;
    tr.load(QString(":/qml/i18n/lang_") + locale + QString(".qm"));
    app.installTranslator(&tr);

    QQmlApplicationEngine engine;
    QQmlContext* ctxt = engine.rootContext();

    UndoManager manager;

    TreeViewModel* model = new TreeViewModel;
    //new ModelTest(model);

    model->populateModel();

    ctxt->setContextProperty("undoManager", &manager);
    ctxt->setContextProperty("externTreeModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

//    PrintVisitor printer;
//    model->accept(printer);

    return app.exec();
}
