// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtGraphs API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QQUICKDATAVISSURFACE_P_H
#define QQUICKDATAVISSURFACE_P_H

#include "qquickdatavisitem_p.h"
#include "qsurface3dseries.h"

#include <private/graphsglobal_p.h>
#include <private/surface3dcontroller_p.h>

QT_BEGIN_NAMESPACE

class QValue3DAxis;
class QSurface3DSeries;
class Surface3DController;
class SurfaceSelectionInstancing;
class Q3DSurfaceNG;

class QQuickDataVisSurface : public QQuickDataVisItem
{
    Q_OBJECT
    Q_PROPERTY(QValue3DAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QValue3DAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QValue3DAxis *axisZ READ axisZ WRITE setAxisZ NOTIFY axisZChanged)
    Q_PROPERTY(QSurface3DSeries *selectedSeries READ selectedSeries NOTIFY selectedSeriesChanged)
    Q_PROPERTY(QQmlListProperty<QSurface3DSeries> seriesList READ seriesList CONSTANT)
    Q_PROPERTY(bool flipHorizontalGrid READ flipHorizontalGrid WRITE setFlipHorizontalGrid NOTIFY flipHorizontalGridChanged)
    Q_CLASSINFO("DefaultProperty", "seriesList")

    QML_NAMED_ELEMENT(Surface3DNG)
    QML_ADDED_IN_VERSION(6, 6)

public:
    explicit QQuickDataVisSurface(QQuickItem *parent = 0);
    ~QQuickDataVisSurface();

    QValue3DAxis *axisX() const;
    void setAxisX(QValue3DAxis *axis);
    QValue3DAxis *axisY() const;
    void setAxisY(QValue3DAxis *axis);
    QValue3DAxis *axisZ() const;
    void setAxisZ(QValue3DAxis *axis);

    QQmlListProperty<QSurface3DSeries> seriesList();
    static void appendSeriesFunc(QQmlListProperty<QSurface3DSeries> *list, QSurface3DSeries *series);
    static qsizetype countSeriesFunc(QQmlListProperty<QSurface3DSeries> *list);
    static QSurface3DSeries *atSeriesFunc(QQmlListProperty<QSurface3DSeries> *list, qsizetype index);
    static void clearSeriesFunc(QQmlListProperty<QSurface3DSeries> *list);
    Q_INVOKABLE void addSeries(QSurface3DSeries *series);
    Q_INVOKABLE void removeSeries(QSurface3DSeries *series);

    QSurface3DSeries *selectedSeries() const;
    void setFlipHorizontalGrid(bool flip);
    bool flipHorizontalGrid() const;

protected:
    void componentComplete() override;
    void synchData() override;
    void updateGraph() override;
    void updateSliceGraph() override;
    void handleMousePressedEvent(QMouseEvent *event) override;
    void updateSingleHighlightColor() override;

public Q_SLOTS:
    void handleAxisXChanged(QAbstract3DAxis *axis) override;
    void handleAxisYChanged(QAbstract3DAxis *axis) override;
    void handleAxisZChanged(QAbstract3DAxis *axis) override;

    void handleFlatShadingEnabledChanged();
    void handleWireframeColorChanged();

Q_SIGNALS:
    void axisXChanged(QValue3DAxis *axis);
    void axisYChanged(QValue3DAxis *axis);
    void axisZChanged(QValue3DAxis *axis);
    void selectedSeriesChanged(QSurface3DSeries *series);
    void flipHorizontalGridChanged(bool flip);

private:
    struct SurfaceVertex {
        QVector3D position;
        QVector3D normal;
        QVector2D uv;
        QPoint coord;
    };

    struct SurfaceModel {
        QQuick3DModel *model;
        QQuick3DModel *gridModel;
        QQuick3DModel *sliceModel;
        QQuick3DModel *sliceGridModel;
        QVector<SurfaceVertex> vertices;
        QVector<SurfaceVertex> coarceVertices;
        QVector<quint32> indices;
        QVector<quint32> gridIndices;
        QVector<float> height;
        QSurface3DSeries *series;
        int columnCount;
        int rowCount;
        SurfaceVertex selectedVertex;
        bool picked = false;
    };

    QVector3D getNormalizedVertex(SurfaceModel *model, const QSurfaceDataItem &data, bool polar, bool flipXZ);
    void createSmoothNormalBodyLine(SurfaceModel *model, int &totalIndex, int column);
    void createSmoothNormalUpperLine(SurfaceModel *model, int &totalIndex);
    void createSmoothIndices(SurfaceModel *model, int x, int y, int endX, int endY);
    void createCoarseVertices(SurfaceModel *model, int x, int y, int endX, int endY);
    void createGridlineIndices(SurfaceModel *model, int x, int y, int endX, int endY);
    void handleChangedSeries();
    void updateModel(SurfaceModel *model);
    void updateSelectedPoint();
    void addModel(QSurface3DSeries *series);

    QVector<SurfaceModel *> m_model;
    Surface3DController *m_surfaceController;
    QQuick3DModel *m_selectionPointer = nullptr;
    SurfaceSelectionInstancing *m_instancing = nullptr;
    QQuick3DModel *m_sliceSelectionPointer = nullptr;
    SurfaceSelectionInstancing *m_sliceInstancing = nullptr;


    friend class Q3DSurfaceNG;
};

QT_END_NAMESPACE

#endif // QQUICKDATAVISSURFACE_P_H
