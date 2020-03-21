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

struct SGResponse
{
    bool        is_success = false;
    QString     msgfrom;
    QString     msgtgt;
};

struct SuperGroupData
{
    enum : uint32_t { class_version = 1 };  // v1: Creation
    QString     m_sg_titles[3];             // Eventually we'll need to support additional titles (I6+)
    QString     m_sg_name;                  // 64 chars max. Here for quick lookup.
    QString     m_sg_created_date;
    QString     m_sg_motto;
    QString     m_sg_motd;
    QString     m_sg_emblem;                // 128 chars max -> Emblem hash table key from the CostumeString_HTable.
    uint32_t    m_sg_colors[2] = {0};
    uint32_t    m_sg_db_id;
    uint32_t    m_sg_leader_db_id = 0;

    template<class Archive>
    void serialize(Archive &archive, uint32_t const version);
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
    uint32_t    m_member_db_id  = 0; // db_id of supergroup
    uint32_t    m_date_joined   = 0; // date joined as ms since Jan 1 2000
    uint32_t    m_hours_logged  = 0; // hours logged in sg_mode
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

class SuperGroup
{
public:
        SuperGroup()
            : m_sg_db_id( ++m_sg_idx_counter )
        { }
virtual ~SuperGroup() = default;

        // Member Vars
        uint32_t    m_sg_db_id          = 0;
        QString     m_sg_name;                  // 64 chars max. Must be here for simple DB lookups
        SuperGroupData m_data;
        vSuperGroupRoster m_sg_members;

        uint32_t    m_db_store_flags    = 0;

        // Methods
        void        dump();
        void        listSGMembers();
        void        addSGMember(Entity *e, SGRanks rank);
        void        removeSGMember(Entity *e);
        uint32_t    getSGLeaderDBID();
        bool        makeSGLeader(Entity &tgt);

private:
static  uint32_t  m_sg_idx_counter;
};


/*
 * SG Methods
 */
bool sameSG(Entity &src, Entity &tgt);
SGResponse inviteSG(Entity &src, Entity &tgt);
QString kickSG(Entity &src, Entity &tgt);
void leaveSG(Entity &e);
bool toggleSGMode(Entity &e);
QString setSGMOTD(Entity &e, const QString &motd);
QString setSGMotto(Entity &e, const QString &motto);
QString setSGTitle(Entity &e, int idx, const QString &title);
QString modifySGRank(Entity &src, Entity &tgt, int rank_mod);
QString demoteSG(Entity &src, Entity &tgt);

SuperGroupStats *getSGMember(Entity &tgt, uint32_t sg_idx);
SuperGroup* getSuperGroupByIdx(uint32_t sg_idx);
void addSuperGroup(Entity &e, SuperGroupData data);
void removeSuperGroup(uint32_t sg_db_id);

extern std::vector<SuperGroup> g_all_supergroups;


/*
 * Mark for db update
 */
enum class SuperGroupDbStoreFlags : uint32_t
{
    Data    = 1,
    Members = 2,
    Full    = ~0U,
};

void markSuperGroupForDbStore(SuperGroup *sg, SuperGroupDbStoreFlags f);
void unmarkSuperGroupForDbStore(SuperGroup *sg, SuperGroupDbStoreFlags f);
