/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#pragma once
#include "GameCommandList.h"

#include "MapEvents.h"
#include "MapLink.h"

#include <QtCore/QString>

// [[ev_def:type]]
class AddTimeStateLog final : public GameCommand
{
public:
    // [[ev_def:field]]
    int m_time_log; // std::time instead?

    AddTimeStateLog(int time_log) : GameCommand(MapEventTypes::evAddTimeStateLog),
        m_time_log(time_log)
    {
    }
    void    serializeto(BitStream &bs) const override {
        bs.StorePackedBits(1,type()-MapEventTypes::evFirstServerToClient);

        bs.StorePackedBits(1, m_time_log);
    }
    void    serializefrom(BitStream &src);
};