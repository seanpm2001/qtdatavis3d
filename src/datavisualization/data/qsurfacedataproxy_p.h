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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QSURFACEDATAPROXY_P_H
#define QSURFACEDATAPROXY_P_H

#include "qsurfacedataproxy.h"
#include "qabstractdataproxy_p.h"

#include <QSize>

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

class QSurfaceDataProxyPrivate : public QAbstractDataProxyPrivate
{
    Q_OBJECT
public:
    QSurfaceDataProxyPrivate(QSurfaceDataProxy *q);
    virtual ~QSurfaceDataProxyPrivate();

    bool resetArray(QSurfaceDataArray *newArray);

    void setValueRangeRows(qreal min, qreal max);
    void setValueRangeColumns(qreal min, qreal max);
    void setMinValueRows(qreal min);
    void setMaxValueRows(qreal max);
    void setMinValueColumns(qreal min);
    void setMaxValueColumns(qreal max);

    qreal rowValue(int segment, int segmentCount);
    qreal columnValue(int segment, int segmentCount);

private:
    QSurfaceDataProxy *qptr();
    QSurfaceDataArray *m_dataArray;
    qreal m_minValueRows;
    qreal m_maxValueRows;
    qreal m_minValueColumns;
    qreal m_maxValueColumns;

    friend class QSurfaceDataProxy;
};

QT_DATAVISUALIZATION_END_NAMESPACE

#endif // QSURFACEDATAPROXY_P_H
