/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#pragma once
#include "CommonNetStructures.h"
#include "Costume.h"

class Entity;
class SuperGroup;

enum class SGRanks : uint32_t
{
    Member  = 0,
    Captain = 1,
    Leader  = 2,
};

/*
 * SuperGroupStats
 */
struct SuperGroupStats
{
    enum : uint32_t { class_version = 1 };  // v1: Creation
    bool        m_has_supergroup    = false;
    uint32_t    m_sg_db_id          = 0;
    SGRanks     m_rank              = SGRanks::Member; // This character's rank in the SG
    bool        m_has_sg_costume    = false; // player has a sg costume
    bool        m_sg_mode           = false; // player uses sg costume currently
    Costume     m_sg_costume;

    // The below are needed by /sgstats
    uint32_t    m_member_db_id  = 0; // db_id of member
    uint32_t    m_hours_logged  = 0; // hours logged in sg_mode
    uint32_t    m_date_joined   = 0; // date joined as ms since Jan 1 2000
    uint32_t    m_last_online   = 0; // last online as ms since Jan 1 2000
    bool        m_is_online     = false;
    QString     m_name;
    QString     m_sg_name;
    QString     m_origin_icon;
    QString     m_class_icon;

    template<class Archive>
    void serialize(Archive &archive, uint32_t const version);

    SuperGroup *getSuperGroup();
    void        dump();
};

using vSuperGroupRoster = std::vector<SuperGroupStats>;
