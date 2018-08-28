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

#include "trays_serializers.h"
//#include "trays_definitions.h"
#include "serialization_common.h"

#include "Logging.h"

const constexpr uint32_t PowerTrayItem::class_version;
const constexpr uint32_t PowerTray::class_version;
const constexpr uint32_t PowerTrayGroup::class_version;

CEREAL_CLASS_VERSION(PowerTrayItem, PowerTrayItem::class_version)   // register PowerTrayItem class version
CEREAL_CLASS_VERSION(PowerTray, PowerTray::class_version)           // register PowerTray class version
CEREAL_CLASS_VERSION(PowerTrayGroup, PowerTrayGroup::class_version) // register PowerTrayGroup class version

template<class Archive>
void serialize(Archive &archive, PowerTrayItem &pwr, uint32_t const version)
{
    if (version != PowerTrayItem::class_version)
    {
        qCritical() << "Failed to serialize PowerTrayItem, incompatible serialization format version " << version;
        return;
    }

    archive(cereal::make_nvp("EntryType", pwr.m_entry_type));
    archive(cereal::make_nvp("PowerSetIdx", pwr.m_pset_idx));
    archive(cereal::make_nvp("PowerIdx", pwr.m_pow_idx));
    archive(cereal::make_nvp("Command", pwr.m_command));
    archive(cereal::make_nvp("ShortName", pwr.m_short_name));
    archive(cereal::make_nvp("IconName", pwr.m_icon_name));
}

template<class Archive>
void serialize(Archive &archive, PowerTray &ptray, uint32_t const version)
{
    if (version != PowerTray::class_version)
    {
        qCritical() << "Failed to serialize PowerTray, incompatible serialization format version " << version;
        return;
    }

    archive(cereal::make_nvp("Powers", ptray.m_tray_items));
}

template<class Archive>
void serialize(Archive &archive, PowerTrayGroup &ptraygroup, uint32_t const version)
{
    if (version != PowerTrayGroup::class_version)
    {
        qCritical() << "Failed to serialize PowerTrayGroup, incompatible serialization format version " << version;
        return;
    }

    archive(cereal::make_nvp("DefaultPowerSet", ptraygroup.m_default_pset_idx));
    archive(cereal::make_nvp("DefaultPower", ptraygroup.m_default_pow_idx));
    archive(cereal::make_nvp("PowerTrays", ptraygroup.m_trays));
}

void saveTo(const PowerTrayGroup &target, const QString &baseName, bool text_format)
{
    commonSaveTo(target,"PowerTrayGroups",baseName,text_format);
}

template
void serialize<cereal::JSONOutputArchive>(cereal::JSONOutputArchive & archive, PowerTrayGroup & m, uint32_t const version);
template
void serialize<cereal::JSONInputArchive>(cereal::JSONInputArchive & archive, PowerTrayGroup & m, uint32_t const version);

void serializeToDb(const PowerTrayGroup &data, QString &tgt)
{
    std::ostringstream ostr;
    {
        cereal::JSONOutputArchive ar(ostr);
        ar(data);
    }
    tgt = QString::fromStdString(ostr.str());
}

void serializeFromDb(PowerTrayGroup &data, const QString &src)
{
    if(src.isEmpty())
        return;
    std::istringstream istr;
    istr.str(src.toStdString());
    {
        cereal::JSONInputArchive ar(istr);
        ar(data);
    }
}
//! @}
