// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef RAINFALLGRAPH_H
#define RAINFALLGRAPH_H

#include "variantbardataproxy.h"
#include <QtGraphs/q3dbars.h>

class RainfallGraph : public QObject
{
    Q_OBJECT
public:
    explicit RainfallGraph(Q3DBarsNG *rainfall);
    ~RainfallGraph();

    void addDataSet();
    void start();

private:

    void updateYearsList(int start, int end);
    Q3DBarsNG *m_graph;
    int m_columnCount;
    int m_rowCount;
    QStringList m_years;
    QStringList m_numericMonths;
    VariantBarDataProxy *m_proxy;
    VariantBarDataMapping *m_mapping;
    VariantDataSet *m_dataSet;
};


#endif
