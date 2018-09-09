/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#pragma once
#include "GameCommand.h"
#include "MapEventTypes.h"
#include "NetStructures/Costume.h"
#include "NetStructures/SuperGroup.h"
#include "Colors.h"
#include "Logging.h"

#include <QtCore/QString>

namespace SEGSEvents
{
// [[ev_def:type]]
class SuperGroupOffer final : public GameCommandEvent
{
public:
    // [[ev_def:field]]
    uint32_t m_db_id;
    // [[ev_def:field]]
    QString m_name;

explicit SuperGroupOffer() : GameCommandEvent(MapEventTypes::evSuperGroupOffer) {}
    SuperGroupOffer(uint32_t &db_id, QString &name) : GameCommandEvent(MapEventTypes::evSuperGroupOffer),
        m_db_id(db_id),
        m_name(name)
    {
    }
    void    serializeto(BitStream &bs) const override {
        bs.StorePackedBits(1,type()-MapEventTypes::evFirstServerToClient); // 29

        bs.StoreBits(32,m_db_id);   // sg offeree db_id
        bs.StoreString(m_name);     // sg offerer name
        qCDebug(logSuperGroups) << "SuperGroupOffer";
    }
    void    serializefrom(BitStream &src);
    EVENT_IMPL(SuperGroupOffer)
};

// [[ev_def:type]]
class SuperGroupResponse final : public GameCommandEvent
{
public:
    // [[ev_def:field]]
    bool m_success;

explicit SuperGroupResponse() : GameCommandEvent(MapEventTypes::evSuperGroupResponse) {}
    SuperGroupResponse(bool &success) : GameCommandEvent(MapEventTypes::evSuperGroupResponse),
        m_success(success)
    {
    }
    void    serializeto(BitStream &bs) const override {
        bs.StorePackedBits(1,type()-MapEventTypes::evFirstServerToClient); // 30
        bs.StoreBits(1, m_success);

        qCDebug(logSuperGroups) << "SuperGroupResponse" << m_success;
        // report result
        // send costume
    }
    void    serializefrom(BitStream &src);
    EVENT_IMPL(SuperGroupResponse)
};

// [[ev_def:type]]
class SuperGroupCostume final : public GameCommandEvent
{
public:
    // [[ev_def:field]]
    Costume m_costume;
    // [[ev_def:field]]
    const ColorAndPartPacker *m_packer;

explicit SuperGroupCostume() : GameCommandEvent(MapEventTypes::evSuperGroupCostume) {}
    SuperGroupCostume(Costume &costume, ColorAndPartPacker *packer) : GameCommandEvent(MapEventTypes::evSuperGroupCostume),
        m_costume(costume),
        m_packer(packer)
    {
    }
    void    serializeto(BitStream &bs) const override {
        bs.StorePackedBits(1,type()-MapEventTypes::evFirstServerToClient); // 31
        // send costume
        //::serializeto(m_costume, bs, *m_packer);
        qCDebug(logSuperGroups) << "SuperGroupCostume";
    }
    void    serializefrom(BitStream &src);
    EVENT_IMPL(SuperGroupCostume)
};

// [[ev_def:type]]
class RegisterSuperGroup final : public GameCommandEvent
{
public:
    // [[ev_def:field]]
    QString m_unknown;

explicit RegisterSuperGroup() : GameCommandEvent(MapEventTypes::evRegisterSuperGroup) {}
    RegisterSuperGroup(QString &unknown) : GameCommandEvent(MapEventTypes::evRegisterSuperGroup),
        m_unknown(unknown)
    {
    }
    void    serializeto(BitStream &bs) const override {
        bs.StorePackedBits(1,type()-MapEventTypes::evFirstServerToClient); // 31
        bs.StoreString(m_unknown); // unknown
        qCDebug(logSuperGroups) << "RegisterSuperGroup:" << m_unknown;
    }
    void    serializefrom(BitStream &src);
    EVENT_IMPL(RegisterSuperGroup)
};

// [[ev_def:type]]
class SuperGroupMode final : public MapLinkEvent
{
public:
    SuperGroupMode() : MapLinkEvent(MapEventTypes::evSuperGroupMode)
    {
    }
    void    serializeto(BitStream &bs) const override
    {
        bs.StorePackedBits(1,type()-MapEventTypes::evFirstServerToClient); // 53
    }
    void    serializefrom(BitStream &bs)
    {
        qCDebug(logSuperGroups) << "Changing SuperGroup Mode";
    }
    EVENT_IMPL(SuperGroupMode)
};

// [[ev_def:type]]
class CreateSuperGroup final : public MapLinkEvent
{
public:
    // [[ev_def:field]]
    SuperGroupData data;

    CreateSuperGroup() : MapLinkEvent(MapEventTypes::evCreateSuperGroup)
    {
    }
    void    serializeto(BitStream &bs) const override
    {
        bs.StorePackedBits(1,type()-MapEventTypes::evFirstServerToClient); // 57
    }
    void    serializefrom(BitStream &bs)
    {
        bs.GetString(data.m_sg_name);
        bs.GetString(data.m_sg_titles[0]);
        bs.GetString(data.m_sg_titles[1]);
        bs.GetString(data.m_sg_titles[2]);
        bs.GetString(data.m_sg_emblem);
        data.m_sg_colors[0] = RGBA(bs.GetPackedBits(32));
        data.m_sg_colors[1] = RGBA(bs.GetPackedBits(32));
        qCDebug(logSuperGroups) << "CreateSuperGroup";
    }
    EVENT_IMPL(CreateSuperGroup)
};

// [[ev_def:type]]
class ChangeSuperGroupColors final : public MapLinkEvent
{
public:
    // [[ev_def:field]]
    RGBA m_sg_colors[2];

    ChangeSuperGroupColors() : MapLinkEvent(MapEventTypes::evChangeSuperGroupColors)
    {
    }
    void    serializeto(BitStream &bs) const override
    {
        bs.StorePackedBits(1,type()-MapEventTypes::evFirstServerToClient); // 58
    }
    void    serializefrom(BitStream &bs)
    {
        m_sg_colors[0] = RGBA(bs.GetPackedBits(32));
        m_sg_colors[1] = RGBA(bs.GetPackedBits(32));
        qCDebug(logSuperGroups) << "Changing SuperGroup Colors";
    }
    EVENT_IMPL(ChangeSuperGroupColors)
};

// [[ev_def:type]]
class CancelSuperGroupCreation final : public MapLinkEvent
{
public:
    CancelSuperGroupCreation() : MapLinkEvent(MapEventTypes::evCancelSuperGroupCreation)
    {
    }
    void    serializeto(BitStream &bs) const override
    {
        bs.StorePackedBits(1,type()-MapEventTypes::evFirstServerToClient); // 59
    }
    void    serializefrom(BitStream &bs)
    {
        qCDebug(logSuperGroups) << "Cancel SuperGroup Creation";
    }
    EVENT_IMPL(CancelSuperGroupCreation)
};
} // end of SEGSEvents namespace