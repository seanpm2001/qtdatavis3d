/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Data Visualization module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef COLORGRADIENT_P_H
#define COLORGRADIENT_P_H

#include "datavisualizationglobal_p.h"
#include <QtGui/QColor>
#include <QtQml/QQmlListProperty>

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class ColorGradientStop : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    ColorGradientStop(QObject *parent = 0);

    qreal position() const;
    void setPosition(qreal position);

    QColor color() const;
    void setColor(const QColor &color);

Q_SIGNALS:
    void positionChanged(qreal position);
    void colorChanged(QColor color);

private:
    void updateGradient();

private:
    qreal m_position;
    QColor m_color;
};

class ColorGradient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<ColorGradientStop> stops READ stops)
    Q_CLASSINFO("DefaultProperty", "stops")

public:
    ColorGradient(QObject *parent = 0);
    ~ColorGradient();

    QQmlListProperty<ColorGradientStop> stops();

    void doUpdate();
    QList<ColorGradientStop *> m_stops;

Q_SIGNALS:
    void updated();
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
