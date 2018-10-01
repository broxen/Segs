/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

/*!
 * @addtogroup MotionTest Projects/CoX/Utilities/MotionTest
 * @{
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MotionTest.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setSceneRect(-200, -200, 300, 300);

    QPen mypen = QPen(Qt::red);

    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomRight(), scene->sceneRect().bottomLeft());
    QLineF LeftLine(scene->sceneRect().bottomLeft(), scene->sceneRect().topLeft());

    scene->addLine(TopLine, mypen);
    scene->addLine(RightLine, mypen);
    scene->addLine(BottomLine, mypen);
    scene->addLine(LeftLine, mypen);

    int ItemCount = 25;
    for(int i = 0; i < ItemCount; i++)
    {
        MotionTest *item = new MotionTest();
        scene->addItem(item);
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene,SLOT(advance()));
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//!@}

