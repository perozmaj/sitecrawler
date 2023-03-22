#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "SiteCrawlerModel.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    SiteCrawlerModel siteCrawlerModel;
    engine.load(QUrl(("qrc:/demo.qml")));
    qmlRegisterType<SiteCrawlerModel>("SiteCrawlerModel", 1, 0 , "SiteCrawlerModel");
    engine.rootContext()->setContextProperty("siteCrawlerModel", &siteCrawlerModel);
    return QGuiApplication::exec();
}
