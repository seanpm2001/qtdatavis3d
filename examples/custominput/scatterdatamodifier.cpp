/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVisualization module.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "scatterdatamodifier.h"

#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/Q3DValueAxis>
#include <QtDataVisualization/Q3DScene>
#include <QtDataVisualization/Q3DCamera>
#include <QtDataVisualization/QScatter3DSeries>
#include <QtDataVisualization/Q3DTheme>
#include <qmath.h>

using namespace QtDataVisualization;

ScatterDataModifier::ScatterDataModifier(Q3DScatter *scatter)
    : m_graph(scatter),
      m_inputHandler(new CustomInputHandler())
{
    m_graph->setTheme(new Q3DTheme(Q3DTheme::ThemeDigia));
    m_graph->setShadowQuality(QDataVis::ShadowQualitySoftLow);
    m_graph->scene()->activeCamera()->setCameraPreset(QDataVis::CameraPresetFront);

    m_graph->setAxisX(new Q3DValueAxis);
    m_graph->setAxisY(new Q3DValueAxis);
    m_graph->setAxisZ(new Q3DValueAxis);

    QScatter3DSeries *series = new QScatter3DSeries;
    series->setItemLabelFormat("@xLabel, @yLabel, @zLabel");
    series->setMesh(QAbstract3DSeries::MeshCube);
    m_graph->addSeries(series);

    //! [2]
    m_animationCameraX = new QPropertyAnimation(m_graph->scene()->activeCamera(), "xRotation");
    m_animationCameraX->setDuration(20000);
    m_animationCameraX->setStartValue(QVariant::fromValue(0.0f));
    m_animationCameraX->setEndValue(QVariant::fromValue(360.0f));
    m_animationCameraX->setLoopCount(-1);
    //! [2]

    //! [3]
    QPropertyAnimation *upAnimation = new QPropertyAnimation(m_graph->scene()->activeCamera(), "yRotation");
    upAnimation->setDuration(9000);
    upAnimation->setStartValue(QVariant::fromValue(5.0f));
    upAnimation->setEndValue(QVariant::fromValue(45.0f));

    QPropertyAnimation *downAnimation = new QPropertyAnimation(m_graph->scene()->activeCamera(), "yRotation");
    downAnimation->setDuration(9000);
    downAnimation->setStartValue(QVariant::fromValue(45.0f));
    downAnimation->setEndValue(QVariant::fromValue(5.0f));

    m_animationCameraY = new QSequentialAnimationGroup();
    m_animationCameraY->setLoopCount(-1);
    m_animationCameraY->addAnimation(upAnimation);
    m_animationCameraY->addAnimation(downAnimation);
    //! [3]

    m_animationCameraX->start();
    m_animationCameraY->start();

    // Give ownership of the handler to the graph and make it the active handler
    //! [0]
    m_graph->setActiveInputHandler(m_inputHandler);
    //! [0]

    //! [1]
    m_selectionTimer = new QTimer(this);
    m_selectionTimer->setInterval(10);
    m_selectionTimer->setSingleShot(false);
    QObject::connect(m_selectionTimer, &QTimer::timeout, this,
                     &ScatterDataModifier::triggerSelection);
    m_selectionTimer->start();
    //! [1]
}

ScatterDataModifier::~ScatterDataModifier()
{
    delete m_graph;
}

void ScatterDataModifier::start()
{
    addData();
}

void ScatterDataModifier::addData()
{
    QVector<QVector3D> *itemList = new QVector<QVector3D>();

    // Read data items from the file to QVector
    QTextStream stream;
    QFile dataFile(":/data/data.txt");
    if (dataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        stream.setDevice(&dataFile);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            if (line.startsWith("#")) // Ignore comments
                continue;
            QStringList strList = line.split(",", QString::SkipEmptyParts);
            // Each line has three data items: xPos, yPos and zPos value
            if (strList.size() < 3) {
                qWarning() << "Invalid row read from data:" << line;
                continue;
            }
            itemList->append(QVector3D(
                                 strList.at(0).trimmed().toFloat(),
                                 strList.at(1).trimmed().toFloat(),
                                 strList.at(2).trimmed().toFloat()));
        }
    } else {
        qWarning() << "Unable to open data file:" << dataFile.fileName();
    }

    // Add data from the QVector to datamodel
    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize(itemList->count());
    QScatterDataItem *ptrToDataArray = &dataArray->first();
    for (int i = 0; i < itemList->count(); i++) {
        ptrToDataArray->setPosition(itemList->at(i));
        ptrToDataArray++;
    }

    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
}

void ScatterDataModifier::toggleCameraAnimation()
{
    if (m_animationCameraX->state() != QAbstractAnimation::Paused) {
        m_animationCameraX->pause();
        m_animationCameraY->pause();
    } else {
        m_animationCameraX->resume();
        m_animationCameraY->resume();
    }
}

void ScatterDataModifier::triggerSelection()
{
    m_graph->scene()->setSelectionQueryPosition(m_inputHandler->inputPosition());
}

void ScatterDataModifier::shadowQualityUpdatedByVisual(QDataVis::ShadowQuality sq)
{
    int quality = int(sq);
    emit shadowQualityChanged(quality); // connected to a checkbox in main.cpp
}

void ScatterDataModifier::changeShadowQuality(int quality)
{
    QDataVis::ShadowQuality sq = QDataVis::ShadowQuality(quality);
    m_graph->setShadowQuality(sq);
}
