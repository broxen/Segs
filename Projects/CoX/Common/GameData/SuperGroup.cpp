/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

/*!
 * @addtogroup GameData Projects/CoX/Common/GameData
 * @{
 */

#include "SuperGroup.h"

#include "Character.h"
#include "Colors.h"
#include "Entity.h"
#include "EntityHelpers.h"
#include "Logging.h"
#include "Messages/Map/MessageChannels.h"
#include "Servers/MapServer/DataHelpers.h"
#include "SuperGroupStats.h"
#include "TimeHelpers.h"

#include "serialization_common.h"
#include "serialization_types.h"


// global variable -- a supergroup service is probably better
std::vector<SuperGroup> g_all_supergroups;
// Max size is probably hardcoded, but I can't get 75 friends together to check =P
static const uint32_t s_max_sg_size = 75;  // max is 75 in I1 client, later raised to 150


template<class Archive>
void SuperGroupData::serialize(Archive &archive, uint32_t const version)
{
    if(version != SuperGroupData::class_version)
    {
        qCritical() << "Failed to serialize SuperGroupData, incompatible serialization format version " << version;
        return;
    }

    archive(cereal::make_nvp("SgDbId", m_sg_db_id));
    archive(cereal::make_nvp("SgName", m_sg_name));
    archive(cereal::make_nvp("SgCreatedDate", m_sg_created_date));
    archive(cereal::make_nvp("SgMotto", m_sg_motto));
    archive(cereal::make_nvp("SgMotd", m_sg_motd));
    archive(cereal::make_nvp("SgEmblem", m_sg_emblem));
    archive(cereal::make_nvp("SgColors", m_sg_colors));
    archive(cereal::make_nvp("SgTitles", m_sg_titles));
    archive(cereal::make_nvp("SgLeaderID", m_sg_leader_db_id));
}

CEREAL_CLASS_VERSION(SuperGroupData, SuperGroupData::class_version) // register SuperGroupData class version
SPECIALIZE_CLASS_VERSIONED_SERIALIZATIONS(SuperGroupData)


/*
 * SG Methods
 */
uint32_t SuperGroup::m_sg_idx_counter = 0;

void SuperGroup::addSGMember(Entity &e, SGRanks rank)
{
    CharacterData *cd = &e.m_char->m_char_data;

    // If SG is full, or player already has a supergroup, return
    if(m_sg_members.size() >= s_max_sg_size || cd->m_supergroup.m_has_supergroup)
        return;

    SuperGroupStats sgs;
    sgs.m_has_supergroup = true;
    sgs.m_sg_db_id      = m_sg_db_id;
    sgs.m_rank          = rank;
    sgs.m_member_db_id  = e.m_db_id;
    sgs.m_hours_logged  = 0;
    sgs.m_date_joined   = getSecsSince2000Epoch();
    sgs.m_last_online   = getSecsSince2000Epoch();
    sgs.m_is_online     = true;
    sgs.m_name          = e.name();
    sgs.m_sg_name       = m_sg_name;
    sgs.m_origin_icon   = cd->m_origin_name;
    sgs.m_class_icon    = cd->m_class_name;

    // Add member to supergroup member list
    m_sg_members.push_back(sgs);
    // Add supergroup stats to player
    cd->m_supergroup = sgs;
    // Build new SG costume from current costume
    createSGCostume(e, this->m_data);

    if(m_sg_members.size() <= 1)
        m_data.m_sg_leader_db_id = e.m_db_id;

    qCDebug(logSuperGroups) << "Adding" << e.name() << "to supergroup" << m_sg_db_id;
    if(logSuperGroups().isDebugEnabled())
    {
        dump();
        cd->m_supergroup.dump();
    }

}

void SuperGroup::removeSGMember(Entity *e)
{
    CharacterData *cd = &e->m_char->m_char_data;

    qCDebug(logSuperGroups) << "Searching SuperGroup members for" << e->name() << "to remove them.";
    uint32_t id_to_find = e->m_db_id;
    auto iter = std::find_if( m_sg_members.begin(), m_sg_members.end(),
                              [id_to_find](const SuperGroupStats& m)->bool {return id_to_find==m.m_member_db_id;});
    if(iter!=m_sg_members.end())
    {
        if(iter->m_member_db_id == m_data.m_sg_leader_db_id)
            m_data.m_sg_leader_db_id = m_sg_members.front().m_member_db_id;

        iter = m_sg_members.erase(iter);
        // reset everything
        cd->m_supergroup.m_has_supergroup = false;
        cd->m_supergroup.m_has_sg_costume = false;
        cd->m_supergroup.m_sg_mode = false;
        cd->m_supergroup.m_sg_costume = *e->m_char->getCurrentCostume();
        cd->m_supergroup.m_sg_db_id = 0;

        markEntityForUpdate(e, EntityUpdateFlags::SuperGroup);
        markEntityForUpdate(e, EntityUpdateFlags::Costumes);

        qCDebug(logSuperGroups) << "Removing" << iter->m_name << "from SuperGroup" << m_sg_db_id;
        if(logSuperGroups().isDebugEnabled())
            listSGMembers();
    }

    if(m_sg_members.size() == 1)
    {
        qCDebug(logSuperGroups) << "One player left on SuperGroup. Making them leader.";
        if(logSuperGroups().isDebugEnabled())
            listSGMembers();

        m_data.m_sg_leader_db_id = m_sg_members.front().m_member_db_id;

        // TODO: fix new leader's rank somehow. SuperGroupService should resolve this.
    }
}

void SuperGroup::dump()
{
    QString output = "Debugging SuperGroups: " + QString::number(m_sg_db_id)
            + "\n\t name: " + m_data.m_sg_name
            + "\n\t db_id: " + QString::number(m_sg_db_id)
            + "\n\t created_date: " + m_data.m_sg_created_date
            + "\n\t leader db_id: " + QString::number(m_data.m_sg_leader_db_id)
            + "\n\t size: " + QString::number(m_sg_members.size());
    qDebug().noquote() << output;

    listSGMembers();
}

void SuperGroup::listSGMembers()
{
    QString output = "SG Members:";

    for (auto &member : m_sg_members)
        output += "\n\t" + member.m_name + " db_id: " + QString::number(member.m_member_db_id);

    qDebug().noquote() << output;
}

uint32_t SuperGroup::getSGLeaderDBID()
{
    return m_data.m_sg_leader_db_id;
}

bool sameSG(Entity &src, Entity &tgt)
{
    return src.m_char->m_char_data.m_supergroup.m_sg_db_id == tgt.m_char->m_char_data.m_supergroup.m_sg_db_id;
}

bool SuperGroup::makeSGLeader(Entity &tgt)
{
    CharacterData *tgt_cd = &tgt.m_char->m_char_data;

    if(!tgt_cd->m_supergroup.m_has_supergroup
            || m_sg_db_id != tgt_cd->m_supergroup.m_sg_db_id
            || getSGLeaderDBID() == tgt.m_db_id)
        return false;

    m_data.m_sg_leader_db_id = tgt.m_db_id;
    tgt_cd->m_supergroup.m_rank = SGRanks::Leader;

    return true;
}

SGResponse inviteSG(Entity &src, Entity &tgt)
{
    SGResponse response;
    response.is_success = false;

    SuperGroupStats *src_sg = &src.m_char->m_char_data.m_supergroup;
    SuperGroupStats *tgt_sg = &tgt.m_char->m_char_data.m_supergroup;

    if(tgt_sg->m_has_supergroup)
    {
        // NOTE: The client should never let us get to this point
        response.msgfrom = tgt.name() + " already has a SuperGroup.";
        return response;
    }

    if(tgt.name() == src.name())
    {
        response.msgfrom = "You cannot invite yourself to a supergroup.";
        return response;
    }

    if(src_sg->m_has_supergroup && src_sg->m_rank < SGRanks::Captain)
    {
        response.msgfrom = "You do not have high enough rank to invite players to the SuperGroup.";
        return response;
    }

    SuperGroup * sg = getSuperGroupByIdx(src_sg->m_sg_db_id);
    if(sg == nullptr)
        qFatal("getSuperGroupByIdx returned nullptr for inviteSG");

    response.is_success = true;
    response.msgfrom = "Inviting " + tgt.name() + " to SuperGroup.";
    response.msgtgt = src.name() + " has invited you to join their SuperGroup.";

    sg->addSGMember(tgt, SGRanks::Member);
    markSuperGroupForDbStore(sg, SuperGroupDbStoreFlags::Full);
    return response;
}

QString kickSG(Entity &src, Entity &tgt)
{
    QString msg = "Kicking " + tgt.name() + " from SuperGroup.";

    SuperGroupStats *src_sg = &src.m_char->m_char_data.m_supergroup;
    SuperGroupStats *tgt_sg = &tgt.m_char->m_char_data.m_supergroup;

    if(!tgt_sg->m_has_supergroup || !sameSG(src, tgt))
        return msg = tgt.name() + " is not in your SuperGroup.";

    if(src_sg->m_rank < SGRanks::Captain)
        return msg = src.name() + " does not have authority to kick SuperGroup members.";

    SuperGroup * sg = getSuperGroupByIdx(tgt_sg->m_sg_db_id);
    if(sg == nullptr)
        qFatal("getSuperGroupByIdx returned nullptr for kickSG");

    sg->removeSGMember(&tgt);
    markSuperGroupForDbStore(sg, SuperGroupDbStoreFlags::Full);
    return msg;
}

void leaveSG(Entity &e)
{
    CharacterData *cd = &e.m_char->m_char_data;

    if(!cd->m_supergroup.m_has_supergroup)
    {
        qCWarning(logSuperGroups) << "Trying to leave a SuperGroup, but Entity has no SG!?";
        return;
    }

    SuperGroup * sg = getSuperGroupByIdx(cd->m_supergroup.m_sg_db_id);
    if(sg == nullptr)
    {
        qFatal("getSuperGroupByIdx returned nullptr for leaveSG");
        return; // if somehow qFatal doesn't do it
    }

    sg->removeSGMember(&e);

    // if there are no members left, delete SG
    if(sg->m_sg_members.empty())
        removeSuperGroup(sg->m_sg_db_id);

    markSuperGroupForDbStore(sg, SuperGroupDbStoreFlags::Full);
}

bool toggleSGMode(Entity &e)
{
    SuperGroupStats *sgs = &e.m_char->m_char_data.m_supergroup;

    if(!sgs->m_has_supergroup)
    {
        qCWarning(logSuperGroups) << "Trying to change SuperGroup mode, but Entity has no SG!?";
        return false;
    }

    sgs->m_sg_mode = !sgs->m_sg_mode;
    qCDebug(logSuperGroups) << "Toggling SG Mode to" << sgs->m_sg_mode;

    return sgs->m_sg_mode;
}

QString setSGMOTD(Entity &e, const QString &motd)
{
    QString msg = "Successfully changed SuperGroup MOTD.";
    SuperGroupStats *sgs = &e.m_char->m_char_data.m_supergroup;

    if(!sgs->m_has_supergroup)
        return msg = "You are not in a SuperGroup.";

    if(sgs->m_rank < SGRanks::Captain)
        return msg = "You do not have the authority to set the SuperGroup MOTD.";

    if(motd.isEmpty())
        return msg = "You must provide a new MOTD.";

    SuperGroup * sg = getSuperGroupByIdx(sgs->m_sg_db_id);
    if(sg == nullptr)
        qFatal("getSuperGroupByIdx returned nullptr for setSGMOTD");

    sg->m_data.m_sg_motd = motd;
    markSuperGroupForDbStore(sg, SuperGroupDbStoreFlags::Full);
    return msg;
}

QString setSGMotto(Entity &e, const QString &motto)
{
    QString msg = "Successfully changed SuperGroup Motto.";
    SuperGroupStats *sgs = &e.m_char->m_char_data.m_supergroup;

    if(!sgs->m_has_supergroup)
        return msg = "You are not in a SuperGroup.";

    if(sgs->m_rank < SGRanks::Captain)
        return msg = "You do not have the authority to set the SuperGroup Motto.";

    if(motto.isEmpty())
        return msg = "You must provide a new Motto.";

    SuperGroup * sg = getSuperGroupByIdx(sgs->m_sg_db_id);
    if(sg == nullptr)
        qFatal("getSuperGroupByIdx returned nullptr for setSGMotto");

    sg->m_data.m_sg_motto = motto;
    markSuperGroupForDbStore(sg, SuperGroupDbStoreFlags::Full);
    return msg;
}

QString setSGTitle(Entity &e, int idx, const QString &title)
{
    SuperGroupStats *sgs = &e.m_char->m_char_data.m_supergroup;
    SuperGroup * sg = getSuperGroupByIdx(sgs->m_sg_db_id);
    if(sg == nullptr)
        qFatal("getSuperGroupByIdx returned nullptr for setSGTitle");

    // limit idx to 0...2
    idx = std::min(std::max(idx,0),2);
    QString msg = "Setting SuperGroup rank titles for " + sg->m_data.m_sg_name;

    switch(idx)
    {
    case 0:
        msg = "Setting Leader title to ";
        break;
    case 1:
        msg = "Setting Captain title to ";
        break;
    case 2:
        msg = "Setting Member title to ";
        break;
    }

    msg += title;
    sg->m_data.m_sg_titles[idx] = title;
    markSuperGroupForDbStore(sg, SuperGroupDbStoreFlags::Full);
    return msg;
}

QString modifySGRank(Entity &src, Entity &tgt, int rank_mod)
{
    QString msg = "Modifying " + tgt.name() + "'s rank in SuperGroup by " + QString::number(rank_mod);

    SuperGroupStats *src_sg = &src.m_char->m_char_data.m_supergroup;
    SuperGroupStats *tgt_sg = &tgt.m_char->m_char_data.m_supergroup;

    if(!tgt_sg->m_has_supergroup || !sameSG(src, tgt))
        return msg = tgt.name() + " is not in your SuperGroup.";

    if(src_sg->m_rank < SGRanks::Leader)
        return msg = src.name() + " does not have authority to promote/demote SuperGroup members.";

    if(rank_mod == 0)
        return msg = "SuperGroup rank unmodified.";

    if((tgt_sg->m_rank == SGRanks::Leader && rank_mod > 0) || (tgt_sg->m_rank == SGRanks::Member && rank_mod < 0))
        return msg = tgt.name() + " cannot modify rank outside of range 1 to 3.";

    SuperGroupStats *tgt_revised = getSGMember(tgt, src_sg->m_sg_db_id);
    if(tgt_revised == nullptr)
        return msg = "getSGMember returned nullptr for promoteSG";

    uint32_t new_rank = static_cast<uint32_t>(tgt_sg->m_rank) + rank_mod;
    new_rank = std::min(std::max(rank_mod,0),2); // if somehow we messed up, limit range from 1 to 3.

    tgt_sg->m_rank = tgt_revised->m_rank = SGRanks(new_rank);

    SuperGroup * sg = getSuperGroupByIdx(tgt_sg->m_sg_db_id);
    if(sg == nullptr)
        qFatal("getSuperGroupByIdx returned nullptr for modifySGRank");

    markSuperGroupForDbStore(sg, SuperGroupDbStoreFlags::Full);
    return msg;
}


SuperGroupStats* getSGMember(Entity &tgt, uint32_t sg_idx)
{
    int idx = -1;

    qCDebug(logSuperGroups) << "Searching for SuperGroup Member" << tgt.name();
    if(sg_idx == 0 || !tgt.m_char->m_char_data.m_supergroup.m_has_supergroup)
        return nullptr;

    SuperGroup *sg = getSuperGroupByIdx(sg_idx);
    if(sg == nullptr)
        qFatal("getSuperGroupByIdx returned nullptr for getSGMember");

    uint32_t id_to_find = tgt.m_char->m_db_id;
    auto iter = std::find_if( sg->m_sg_members.begin(), sg->m_sg_members.end(),
                              [id_to_find](const SuperGroupStats& m)->bool {return id_to_find==m.m_member_db_id;});
    if(iter != sg->m_sg_members.end())
    {
        qCDebug(logSuperGroups) << "Returning SuperGroup Member" << iter->m_name;
        idx = std::distance(sg->m_sg_members.begin(), iter);
    }

    if(idx == -1)
        return nullptr;

    return &sg->m_sg_members.at(idx);
}

SuperGroup* getSuperGroupByIdx(uint32_t sg_idx)
{
    //qCDebug(logSuperGroups) << "Searching for SuperGroup" << sg_idx;
    if(sg_idx != 0 && sg_idx <= g_all_supergroups.size())
        return &g_all_supergroups.at(sg_idx-1);

    return nullptr;
}

void setSuperGroup(Entity &e, bool has_sg, QString &sg_name)
{
    CharacterData *cd = &e.m_char->m_char_data;

    if(has_sg == false)
    {
        cd->m_supergroup.m_has_supergroup = false;
        cd->m_supergroup.m_sg_db_id = 0;
        cd->m_supergroup.m_rank = SGRanks::Member;
        cd->m_supergroup.m_has_sg_costume = false;
        return;
    }

    SuperGroupData sgd;
    sgd.m_sg_name       = sg_name;
    sgd.m_sg_titles[0]  = "Leader";
    sgd.m_sg_titles[1]  = "Captain";
    sgd.m_sg_titles[2]  = "Member";
    sgd.m_sg_emblem     = "Torch_01";
    sgd.m_sg_colors[0]  = 0x996633FF; //0x9799FF
    sgd.m_sg_colors[1]  = 0x336699FF; //0xD48C00FF 0x553800FF
    sgd.m_sg_leader_db_id = e.m_idx;
    sgd.m_sg_motd       = "MOTD Test";
    sgd.m_sg_motto      = "MOTTO Test";

    addSuperGroup(e, sgd);

    SuperGroup * sg = getSuperGroupByIdx(cd->m_supergroup.m_sg_db_id);
    if(sg == nullptr)
    {
        qFatal("getSuperGroupByIdx returned nullptr");
        return; // if somehow qFatal doesn't do it
    }
}

void addSuperGroup(Entity &e, SuperGroupData &data)
{
    SuperGroup sg;
    sg.m_data.m_sg_name         = data.m_sg_name;
    sg.m_data.m_sg_created_date = getSecsSince2000Epoch();
    sg.m_data.m_sg_motto        = data.m_sg_motto;
    sg.m_data.m_sg_motd         = data.m_sg_motd;
    sg.m_data.m_sg_emblem       = data.m_sg_emblem;
    sg.m_data.m_sg_leader_db_id = data.m_sg_leader_db_id;
    sg.m_data.m_sg_titles[0]    = data.m_sg_titles[0];
    sg.m_data.m_sg_titles[1]    = data.m_sg_titles[1];
    sg.m_data.m_sg_titles[2]    = data.m_sg_titles[2];
    sg.m_data.m_sg_colors[0]    = data.m_sg_colors[0];
    sg.m_data.m_sg_colors[1]    = data.m_sg_colors[1];

    sg.addSGMember(e, SGRanks::Leader);
    g_all_supergroups.push_back(sg);

    markEntityForUpdate(&e, EntityUpdateFlags::SuperGroup);
}

void removeSuperGroup(uint32_t sg_db_id)
{
    auto iter = std::find_if( g_all_supergroups.begin(), g_all_supergroups.end(),
                              [sg_db_id](const SuperGroup& sg)->bool {return sg_db_id==sg.m_sg_db_id;});
    if(iter!=g_all_supergroups.end())
        iter = g_all_supergroups.erase(iter);
}

bool isSuperGroupValid(QString &name)
{
    // TODO: Check to ensure name isn't already in use or restricted
    // if(isSGNameIsInvalid(data.m_sg_name) || isSGNameTaken(data.m_sg_name))
    //     return false;

    // For now let's simply provide a means for testing
    if(name.contains("Success", Qt::CaseInsensitive))
        return true;

    return false; // client sends "Invalid SuperGroup Name" msg
}

void setSGCostumeColors(Costume &costume, uint32_t colors[])
{
    uint32_t pri_color_slot;
    uint32_t sec_color_slot;
    uint32_t index;

    // Colors are alternated depending upon the part
    for(auto &part : costume.m_parts)
    {
        pri_color_slot = (colors[0] >> 2 * index) & 3;
        sec_color_slot = (colors[1] >> 2 * index) & 3;

        if(pri_color_slot == 2)
            part.m_colors[0] = RGBA(colors[0]).toABGR();
        else if(pri_color_slot == 3)
            part.m_colors[0] = RGBA(colors[1]).toABGR();

        if(sec_color_slot == 2)
            part.m_colors[1] = RGBA(colors[0]).toABGR();
        else if(sec_color_slot == 3)
            part.m_colors[1] = RGBA(colors[1]).toABGR();

        ++index;
    }
}

void createSGCostume(Entity &e, SuperGroupData &data)
{
    SuperGroupStats &sgs = e.m_char->m_char_data.m_supergroup;

    // if we already have a costume, return
    if(sgs.m_has_sg_costume)
        return;

    // set SG Costume to current costume
    sgs.m_sg_costume = *e.m_char->getCurrentCostume();

    // if Emblem is set, change it and change costume top if necessary
    if(!data.m_sg_emblem.isEmpty())
    {
        // We can't be sure that these parts will always be at the same idx.
        // Get idx of "Chest" and "ChestDetail" in parts array
        uint32_t chest_idx = distance(sgs.m_sg_costume.m_parts.begin(), std::find_if(
                                        sgs.m_sg_costume.m_parts.begin(),
                                        sgs.m_sg_costume.m_parts.end(),
                                        [] (const CostumePart& cp) { return cp.m_type == uint8_t(CostumePartType::Chest); }));
        uint32_t chest_detail_idx = distance(sgs.m_sg_costume.m_parts.begin(), std::find_if(
                                        sgs.m_sg_costume.m_parts.begin(),
                                        sgs.m_sg_costume.m_parts.end(),
                                        [] (const CostumePart& cp) { return cp.m_type == uint8_t(CostumePartType::ChestDetail); }));

        // CoX could only do chest emblems on some peices, let's single those out here
        static const QStringList ok_chest_pieces = { "tight", "jacket", "baggy", "armored"};

        // if chest piece isn't on of the ok types, then change it to "tight"
        if(!ok_chest_pieces.contains(sgs.m_sg_costume.m_parts[chest_idx].m_geometry, Qt::CaseInsensitive))
            sgs.m_sg_costume.m_parts[chest_detail_idx].m_geometry = "tight";

        // set textures
        sgs.m_sg_costume.m_parts[chest_detail_idx].m_texture_1 = "base";
        sgs.m_sg_costume.m_parts[chest_detail_idx].m_texture_2 = qPrintable(data.m_sg_emblem);
    }

    // set SG Colors
    setSGCostumeColors(sgs.m_sg_costume, data.m_sg_colors);

    // flag costumes for update
    sgs.m_has_sg_costume = true;
    sgs.m_sg_costume.m_send_full_costume = true;
    markEntityForUpdate(&e, EntityUpdateFlags::Costumes);
}

/*
 * Mark for db update
 */
void markSuperGroupForDbStore(SuperGroup *sg, SuperGroupDbStoreFlags f)
{
    sg->m_db_store_flags |= uint32_t(f);
}

void unmarkSuperGroupForDbStore(SuperGroup *sg, SuperGroupDbStoreFlags f)
{
    sg->m_db_store_flags &= ~uint32_t(f);
}

//! @}
