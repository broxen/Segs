/*
 * SEGS - Super Entity Game Server
 * http://www.segs.dev/
 * Copyright (c) 2006 - 2020 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

/*!
 * @addtogroup CoXClient Projects/CoX/Clients/Client
 * @{
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QDebug>
#include <QLoggingCategory>

#include "version.h"

int main(int argc, char *argv[])
{
    static const char ENV_VAR_QT_DEVICE_PIXEL_RATIO[] = "QT_DEVICE_PIXEL_RATIO";
    if(!qEnvironmentVariableIsSet(ENV_VAR_QT_DEVICE_PIXEL_RATIO)
        && !qEnvironmentVariableIsSet("QT_AUTO_SCREEN_SCALE_FACTOR")
        && !qEnvironmentVariableIsSet("QT_SCALE_FACTOR")
        && !qEnvironmentVariableIsSet("QT_SCREEN_SCALE_FACTORS")) {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }

    QLoggingCategory::setFilterRules(QStringLiteral("*.debug=true\nqt.*.debug=false"));

    QGuiApplication app(argc, argv);
    app.setOrganizationName(ClientVersionInfo::getProjectOrg());
    app.setOrganizationDomain(ClientVersionInfo::getProjectDomain());
    app.setApplicationName(ClientVersionInfo::getProjectName());
    app.setApplicationVersion(ClientVersionInfo::getVersionNumber());

    QQmlApplicationEngine engine;

    // Print out Project Name and Version to console
    qInfo().noquote() << ClientVersionInfo::getVersionString();
    qInfo().noquote() << ClientVersionInfo::getCopyright();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

//! @}
