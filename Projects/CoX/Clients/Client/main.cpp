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
#include <QQmlContext>

#include "Login/Login.h"
#include "Version/Version.h"

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
    app.setOrganizationName(ClientVersion::getProjectOrg());
    app.setOrganizationDomain(ClientVersion::getProjectDomain());
    app.setApplicationName(ClientVersion::getProjectName());
    app.setApplicationVersion(ClientVersion::getVersionNumber());

    // Print out Project Name and Version to console
    qInfo().noquote() << ClientVersion::getVersionString();
    qInfo().noquote() << ClientVersion::getCopyright();

    QQmlApplicationEngine engine;
    LoginSystem login_system;
    // test some values:
    login_system.setUsername("segsadmin");
    login_system.setUsernameToggle(true);
    login_system.setVersionString(ClientVersion::getVersionString());
    // pass context to QML
    engine.rootContext()->setContextProperty("LoginSystem", &login_system); // the object will be available in QML with name "LoginSystem"

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

//! @}
