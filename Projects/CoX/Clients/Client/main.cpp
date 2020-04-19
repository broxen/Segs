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

#include "Login/Login.h"
#include "Version/Version.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include <QQuickStyle>
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QLoggingCategory>

#include <mutex>

namespace
{

// TODO: this code mirrors code in the server, can we refactor and share code?
void segsClientLogMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static char log_buffer[4096]={0};
    static char category_text[256];
    log_buffer[0] = 0;
    category_text[0] = 0;
    if(strcmp(context.category,"default")!=0)
        snprintf(category_text, sizeof(category_text), "[%s]", context.category);

    QFile client_log_target;
    QDate todays_date(QDate::currentDate());
    QString log_path = QDir::current().absolutePath() + QDir::separator() + QString("logs");
    log_path += QDir::separator() +todays_date.toString("yyyy-MM-dd") + ".log";
    client_log_target.setFileName(log_path);

    if(!client_log_target.open(QFile::WriteOnly | QFile::Append))
    {
        fprintf(stderr,"Failed to open log file in write mode, will procede with console only logging");
    }

    QByteArray localMsg = msg.toLocal8Bit();
    std::string timestamp  = QTime::currentTime().toString("hh:mm:ss").toStdString();

    switch (type)
    {
        case QtDebugMsg:
            snprintf(log_buffer, sizeof(log_buffer), "[%s] %sDebug   : %s\n",
                     timestamp.c_str(), category_text, localMsg.constData());
            break;
        case QtInfoMsg:
            // no prefix or category for informational messages, as these are end-user facing
            snprintf(log_buffer, sizeof(log_buffer), "[%s] %s\n",
                     timestamp.c_str(), localMsg.constData());
            break;
        case QtWarningMsg:
            snprintf(log_buffer, sizeof(log_buffer), "[%s] %sWarning : %s\n",
                     timestamp.c_str(), category_text, localMsg.constData());
            break;
        case QtCriticalMsg:
            snprintf(log_buffer, sizeof(log_buffer), "[%s] %sCritical: %s\n",
                     timestamp.c_str(), category_text, localMsg.constData());
            break;
        case QtFatalMsg:
            snprintf(log_buffer, sizeof(log_buffer), "[%s] %sFatal: %s\n",
                     timestamp.c_str(), category_text, localMsg.constData());
    }

    fprintf(stdout, "%s", log_buffer);
    fflush(stdout);

    if(client_log_target.isOpen())
        client_log_target.write(log_buffer);

    if(type == QtFatalMsg)
    {
        client_log_target.close();
        abort();
    }
}

} // end of anonymous namespace

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
    qInstallMessageHandler(segsClientLogMessageOutput);

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
    // set Version String for footer
    login_system.setVersionString(ClientVersion::getVersionString());
    // TODO: pull these values from local settings.cfg file
    // for now, test some values
    login_system.setUsername("segsadmin");
    login_system.setUsernameToggle(true);
    // pass context to QML
    engine.rootContext()->setContextProperty("LoginSystem", &login_system);

    engine.addImportPath("qrc:/");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

//! @}
