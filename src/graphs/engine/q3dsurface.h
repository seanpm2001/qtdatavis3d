// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef Q3DSURFACE_H
#define Q3DSURFACE_H

#include <QtGraphs/qabstract3dgraph.h>
#include <QtGraphs/qvalue3daxis.h>
#include <QtGraphs/qsurface3dseries.h>
#include <QtQuick/QQuickWindow>

QT_BEGIN_NAMESPACE

class QQuickDataVisSurface;

class Q_GRAPHS_EXPORT Q3DSurfaceNG : public QAbstract3DGraphNG
{
    Q_OBJECT
    Q_PROPERTY(QValue3DAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QValue3DAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QValue3DAxis *axisZ READ axisZ WRITE setAxisZ NOTIFY axisZChanged)
    Q_PROPERTY(QSurface3DSeries *selectedSeries READ selectedSeries NOTIFY selectedSeriesChanged)
    Q_PROPERTY(bool flipHorizontalGrid READ flipHorizontalGrid WRITE setFlipHorizontalGrid NOTIFY flipHorizontalGridChanged)

public:
    explicit Q3DSurfaceNG();
    virtual ~Q3DSurfaceNG();

    void addSeries(QSurface3DSeries *series);
    void removeSeries(QSurface3DSeries *series);
    QList<QSurface3DSeries *> seriesList() const;

    // Axes
    void setAxisX(QValue3DAxis *axis);
    QValue3DAxis *axisX() const;
    void setAxisY(QValue3DAxis *axis);
    QValue3DAxis *axisY() const;
    void setAxisZ(QValue3DAxis *axis);
    QValue3DAxis *axisZ() const;
    void addAxis(QValue3DAxis *axis);
    void releaseAxis(QValue3DAxis *axis);
    QList<QValue3DAxis *> axes() const;

    QSurface3DSeries *selectedSeries() const;
    void setFlipHorizontalGrid(bool flip);
    bool flipHorizontalGrid() const;

Q_SIGNALS:
    void axisXChanged(QValue3DAxis *axis);
    void axisYChanged(QValue3DAxis *axis);
    void axisZChanged(QValue3DAxis *axis);
    void selectedSeriesChanged(QSurface3DSeries *series);
    void flipHorizontalGridChanged(bool flip);

private:
    QQuickDataVisSurface *dptr();
    const QQuickDataVisSurface *dptrc() const;
};

QT_END_NAMESPACE

#endif
