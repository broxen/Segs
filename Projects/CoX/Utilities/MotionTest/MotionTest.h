/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#pragma once
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class MotionTest : public QGraphicsItem
{
public:
    MotionTest();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int phase);

private:
    qreal angle;
    qreal speed;
    void DoCollision();
};
