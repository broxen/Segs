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

#include <QDebug>

#include "Login.h"

LoginSystem::LoginSystem(QObject *parent) :
    QObject(parent)
{
}

QString LoginSystem::getUsername()
{
    return m_username;
}

QString LoginSystem::getPassword()
{
    return m_password;
}

bool LoginSystem::getUsernameToggle()
{
    return m_remember_username;
}

QString LoginSystem::getVersionString()
{
    return m_version_string;
}

void LoginSystem::submitLoginInfo(const QString &username, const QString &password)
{
    qDebug() << "Login Information: " << username << " with " << password;

    // TODO: dialog popup showing login information
}

void LoginSystem::setUsername(const QString &username)
{
    // TODO: if save_username is toggled no, return

    // TODO: get saved username from settings.cfg and send emit signal
    // such as emit setUsername(username_from_cfg);
    if (username != m_username) {
        m_username = username;
        emit usernameChanged();
    }
}

void LoginSystem::setUsernameToggle(bool save)
{
    // if true, we store the username in settings.cfg for use later
    m_remember_username = save;
}

void LoginSystem::setVersionString(const QString &version)
{
    m_version_string = version;
}

//! @}
