/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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
#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qscatter3dseries.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QtCore/qmath.h>

using namespace QtDataVisualization;

static const float verticalRange = 8.0f;
static const float horizontalRange = verticalRange;
static const float ellipse_a = horizontalRange / 3.0f;
static const float ellipse_b = verticalRange;
static const float doublePi = float(M_PI) * 2.0f;
static const float radiansToDegrees = 360.0f / doublePi;
static const float animationFrames = 30.0f;

ScatterDataModifier::ScatterDataModifier(Q3DScatter *scatter)
    : m_graph(scatter),
      m_fieldLines(12),
      m_arrowsPerLine(16),
      m_magneticField(new QScatter3DSeries),
      m_sun(new QScatter3DSeries),
      m_magneticFieldArray(0),
      m_angleOffset(0.0f),
      m_angleStep(doublePi / m_arrowsPerLine / animationFrames)
{
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);

    // Magnetic field lines use custom narrow arrow
    m_magneticField->setItemSize(0.2f);
    //! [3]
    m_magneticField->setMesh(QAbstract3DSeries::MeshUserDefined);
    m_magneticField->setUserDefinedMesh(QStringLiteral(":/mesh/narrowarrow.obj"));
    //! [3]
    //! [4]
    QLinearGradient fieldGradient(0, 0, 16, 1024);
    fieldGradient.setColorAt(0.0, Qt::black);
    fieldGradient.setColorAt(1.0, Qt::white);
    m_magneticField->setBaseGradient(fieldGradient);
    m_magneticField->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    //! [4]

    // For 'sun' we use a custom large sphere.
    m_sun->setItemSize(0.2f);
    m_sun->setName(QStringLiteral("Sun"));
    m_sun->setItemLabelFormat(QStringLiteral("@seriesName"));
    m_sun->setMesh(QAbstract3DSeries::MeshUserDefined);
    m_sun->setUserDefinedMesh(QStringLiteral(":/mesh/largesphere.obj"));
    m_sun->setBaseColor(QColor(0xff, 0xBB, 0x00));
    m_sun->dataProxy()->addItem(QScatterDataItem(QVector3D()));

    m_graph->addSeries(m_magneticField);
    m_graph->addSeries(m_sun);

    // Configure the axes according to the data
    m_graph->axisX()->setRange(-horizontalRange, horizontalRange);
    m_graph->axisY()->setRange(-verticalRange, verticalRange);
    m_graph->axisZ()->setRange(-horizontalRange, horizontalRange);
    m_graph->axisX()->setSegmentCount(int(horizontalRange));
    m_graph->axisZ()->setSegmentCount(int(horizontalRange));

    QObject::connect(&m_rotationTimer, &QTimer::timeout, this,
                     &ScatterDataModifier::triggerRotation);

    toggleRotation();
    generateData();
}

ScatterDataModifier::~ScatterDataModifier()
{
    delete m_graph;
}

void ScatterDataModifier::generateData()
{
    // Reusing existing array is computationally cheaper than always generating new array, even if
    // all data items change in the array, if the array size doesn't change.
    if (!m_magneticFieldArray)
        m_magneticFieldArray = new QScatterDataArray;

    int arraySize = m_fieldLines * m_arrowsPerLine;
    if (arraySize != m_magneticFieldArray->size())
        m_magneticFieldArray->resize(arraySize);

    QScatterDataItem *ptrToDataArray = &m_magneticFieldArray->first();

    for (float i = 0; i < m_fieldLines; i++) {
        float horizontalAngle = (doublePi * i) / m_fieldLines;
        float xCenter = ellipse_a * qCos(horizontalAngle);
        float zCenter = ellipse_a * qSin(horizontalAngle);

        // Rotate - arrow always tangential to origo
        //! [0]
        QQuaternion yRotation = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, horizontalAngle * radiansToDegrees);
        //! [0]

        for (float j = 0; j < m_arrowsPerLine; j++) {
            // Calculate point on ellipse centered on origo and parallel to x-axis
            float verticalAngle = ((doublePi * j) / m_arrowsPerLine) + m_angleOffset;
            float xUnrotated = ellipse_a * qCos(verticalAngle);
            float y = ellipse_b * qSin(verticalAngle);

            // Rotate the ellipse around y-axis
            float xRotated = xUnrotated * qCos(horizontalAngle);
            float zRotated = xUnrotated * qSin(horizontalAngle);

            // Add offset
            float x = xCenter + xRotated;
            float z = zCenter + zRotated;

            //! [1]
            QQuaternion zRotation = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, verticalAngle * radiansToDegrees);
            QQuaternion totalRotation = yRotation * zRotation;
            //! [1]

            ptrToDataArray->setPosition(QVector3D(x, y, z));
            //! [2]
            ptrToDataArray->setRotation(totalRotation);
            //! [2]
            ptrToDataArray++;
        }
    }

    if (m_graph->selectedSeries() == m_magneticField)
        m_graph->clearSelection();

    m_magneticField->dataProxy()->resetArray(m_magneticFieldArray);
}

void ScatterDataModifier::setFieldLines(int lines)
{
    m_fieldLines = lines;
    generateData();
}

void ScatterDataModifier::setArrowsPerLine(int arrows)
{
    m_angleOffset = 0.0f;
    m_angleStep = doublePi / m_arrowsPerLine / animationFrames;
    m_arrowsPerLine = arrows;
    generateData();
}

void ScatterDataModifier::triggerRotation()
{
    m_angleOffset += m_angleStep;
    generateData();
}

void ScatterDataModifier::toggleSun()
{
    m_sun->setVisible(!m_graph->seriesList().at(1)->isVisible());
}

void ScatterDataModifier::toggleRotation()
{
    if (m_rotationTimer.isActive())
        m_rotationTimer.stop();
    else
        m_rotationTimer.start(15);
}
