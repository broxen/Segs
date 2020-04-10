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

#include "SuperGroupStats.h"

#include "Logging.h"
#include "SuperGroup.h"

#include "serialization_common.h"
#include "serialization_types.h"

template<class Archive>
void SuperGroupStats::serialize(Archive &archive, uint32_t const version)
{
    if(version != SuperGroupStats::class_version)
    {
        qCritical() << "Failed to serialize SuperGroupStats, incompatible serialization format version " << version;
        return;
    }

    archive(cereal::make_nvp("SgHasSuperGroup", m_has_supergroup));
    archive(cereal::make_nvp("SgDbId", m_sg_db_id));
    archive(cereal::make_nvp("SgRank", m_rank));
    archive(cereal::make_nvp("SgHasCostume", m_has_sg_costume));
    archive(cereal::make_nvp("SgMode", m_sg_mode));
    archive(cereal::make_nvp("SgCostume", m_sg_costume));
    archive(cereal::make_nvp("SgMemberDbId", m_member_db_id));
    archive(cereal::make_nvp("SgDateJoined", m_date_joined));
    archive(cereal::make_nvp("SgHoursLogged", m_hours_logged));
    archive(cereal::make_nvp("SgLastOnline", m_last_online));
    archive(cereal::make_nvp("SgIsOnline", m_is_online));
    archive(cereal::make_nvp("SgMemberName", m_name));
    archive(cereal::make_nvp("SgName", m_sg_name));
    archive(cereal::make_nvp("SgOriginIcon", m_origin_icon));
    archive(cereal::make_nvp("SgClassIcon", m_class_icon));
}

CEREAL_CLASS_VERSION(SuperGroupStats, SuperGroupStats::class_version) // register SuperGroupData class version
SPECIALIZE_CLASS_VERSIONED_SERIALIZATIONS(SuperGroupStats)


/*
 * SuperGroupStats
 */
SuperGroup* SuperGroupStats::getSuperGroup()
{
    if(m_has_supergroup && m_sg_db_id != 0)
        return getSuperGroupByIdx(m_sg_db_id);

    return nullptr;
}

void SuperGroupStats::dump()
{
    QString msg = QString("SuperGroup Info\n  has_supergroup: %1 \n  db_id: %2 \n  sg_mode: %3 \n  has_sg_costume: %4 \n  rank: %5 ")
            .arg(m_has_supergroup)
            .arg(m_sg_db_id)
            .arg(m_sg_mode)
            .arg(m_has_sg_costume)
            .arg(static_cast<uint32_t>(m_rank));

    qDebug().noquote() << msg;
    m_sg_costume.dump();
}


//! @}
