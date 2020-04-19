/*
 * SEGS Client - Super Entity Game Server Client
 * http://www.segs.dev/
 * Copyright (c) 2006 - 2020 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#pragma once

#include <QObject>
#include <QString>

class LoginSystem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword NOTIFY passwordChanged)
    Q_PROPERTY(bool remember_username READ getUsernameToggle WRITE setUsernameToggle NOTIFY usernameToggleChanged)
    Q_PROPERTY(QString version_string READ getVersionString NOTIFY versionStringChanged)

public:
    explicit LoginSystem(QObject *parent = nullptr);

    QString getUsername();
    QString getPassword();
    bool getUsernameToggle();
    QString getVersionString();

public slots:
    void submitLoginInfo(const QString &username, const QString &password);
    void setUsername(const QString &username);
    void setUsernameToggle(bool save);
    void setVersionString(const QString &version);

signals: // future planning
    void usernameChanged();
    void passwordChanged();
    void usernameToggleChanged();
    void versionStringChanged();

private:
    QString m_username;
    QString m_password;
    bool m_remember_username;
    QString m_version_string;
};
