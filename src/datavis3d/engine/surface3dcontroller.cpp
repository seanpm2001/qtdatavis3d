/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVis3D module.
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

#include "surface3dcontroller_p.h"
#include "surface3drenderer_p.h"
#include "camerahelper_p.h"
#include "q3dabstractaxis_p.h"
#include "q3dvalueaxis_p.h"
#include "q3dcategoryaxis.h"

#include <QMatrix4x4>
#include <QMouseEvent>

#include <QDebug>

QT_DATAVIS3D_BEGIN_NAMESPACE

Surface3DController::Surface3DController(QRect rect)
    : Abstract3DController(rect),
      m_renderer(0),
      m_smoothSurface(false),
      m_surfaceGrid(true),
      m_mouseState(MouseNone),
      m_mousePos(QPoint(0, 0))
{
    // Setting a null axis creates a new default axis according to orientation and chart type.
    // Note: These cannot be set in Abstract3DController constructor, as they will call virtual
    //       functions implemented by subclasses.
    setAxisX(0);
    setAxisY(0);
    setAxisZ(0);
}

Surface3DController::~Surface3DController()
{
}

void Surface3DController::initializeOpenGL()
{
    // Initialization is called multiple times when Qt Quick components are used
    if (isInitialized())
        return;

    m_renderer = new Surface3DRenderer(this);
    setRenderer(m_renderer);
    synchDataToRenderer();
    emitNeedRender();
}

void Surface3DController::synchDataToRenderer()
{
    Abstract3DController::synchDataToRenderer();

    if (!isInitialized())
        return;

    // Notify changes to renderer
}

void Surface3DController::handleAxisAutoAdjustRangeChangedInOrientation(Q3DAbstractAxis::AxisOrientation orientation, bool autoAdjust)
{
    Q_UNUSED(orientation)
    Q_UNUSED(autoAdjust)

    // TODO: Implement!
}

QMatrix4x4 Surface3DController::calculateViewMatrix(int zoom, int viewPortWidth, int viewPortHeight, bool showUnder)
{
    return m_cameraHelper->calculateViewMatrix(m_mousePos,
                                               zoom,
                                               viewPortWidth,
                                               viewPortHeight,
                                               showUnder);
}

void Surface3DController::setSmoothSurface(bool enable)
{
    m_smoothSurface = enable;
    emit smoothStatusChanged(m_smoothSurface);
    emitNeedRender();
}

bool Surface3DController::smoothSurface()
{
    return m_smoothSurface;
}

void Surface3DController::setSurfaceGrid(bool enable)
{
    m_surfaceGrid = enable;
    emit surfaceGridChanged(m_surfaceGrid);
    emitNeedRender();
}

bool Surface3DController::surfaceGrid()
{
    return m_surfaceGrid;
}


#if defined(Q_OS_ANDROID)
void Surface3DController::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}
void touchEvent(QTouchEvent *event)
{
    Q_UNUSED(event)
}
#endif

void Surface3DController::mousePressEvent(QMouseEvent *event, const QPoint &mousePos)
{
    if (Qt::LeftButton == event->button()) {
        m_mousePos = mousePos;
        emit leftMousePressed(mousePos);
    } else if (Qt::RightButton == event->button()) {
    #if !defined(Q_OS_ANDROID)
        m_mouseState = Abstract3DController::MouseRotating;
    #else
        m_mouseState = Abstract3DController::MouseOnScene;
    #endif
        // update mouse positions to prevent jumping when releasing or repressing a button
        m_mousePos = mousePos; //event->pos();
    }
    m_cameraHelper->updateMousePos(m_mousePos);
    emitNeedRender();
}

void Surface3DController::mouseReleaseEvent(QMouseEvent *event, const QPoint &mousePos)
{
    Q_UNUSED(event)
    if (Abstract3DController::MouseRotating == m_mouseState) {
        // update mouse positions to prevent jumping when releasing or repressing a button
        m_mousePos = mousePos; //event->pos();
        m_cameraHelper->updateMousePos(mousePos); //event->pos());
        emitNeedRender();
    }
    m_mouseState = Abstract3DController::MouseNone;
}

void Surface3DController::mouseMoveEvent(QMouseEvent *event, const QPoint &mousePos)
{
    Q_UNUSED(event)
    if (Abstract3DController::MouseRotating == m_mouseState) {
        m_mousePos = mousePos; //event->pos();
        emitNeedRender();
    }
}

void Surface3DController::wheelEvent(QWheelEvent *event)
{
    Q_UNUSED(event)
}

QPoint Surface3DController::mousePosition()
{
    return m_mousePos;
}

void Surface3DController::setSegmentCount(GLint segmentCount, GLfloat step, GLfloat minimum)
{
    m_segmentCount   = segmentCount;
    m_segmentStep    = step;
    m_segmentMinimum = minimum;

    emit segmentCountChanged(m_segmentCount, m_segmentStep, m_segmentMinimum);
    emitNeedRender();
}

void Surface3DController::setGradientColorAt(qreal pos, const QColor &color)
{
    Theme t = theme();
    t.m_surfaceGradient.setColorAt(pos, color);
    emitNeedRender();
}

// TODO: Temp
void Surface3DController::setData(QList<qreal> series, int width, int depth)
{
    m_series = series;
    m_dataWidth = width;
    m_dataDepth = depth;

    m_renderer->setXZStuff(width, depth);
    m_renderer->setSeries(series);
    emitNeedRender();
}

QT_DATAVIS3D_END_NAMESPACE
