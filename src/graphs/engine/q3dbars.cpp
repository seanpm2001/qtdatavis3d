// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "q3dbars.h"
#include "qquickdatavisbars_p.h"

QT_BEGIN_NAMESPACE

/*!
 * \class Q3DBars
 * \inmodule QtGraphs
 * \brief The Q3DBarsNG class provides methods for rendering 3D bar graphs.
 *
 * This class enables developers to render bar graphs in 3D and to view them by rotating the scene
 * freely. Rotation is done by holding down the right mouse button and moving the mouse. Zooming
 * is done by mouse wheel. Selection, if enabled, is done by left mouse button. The scene can be
 * reset to default camera view by clicking mouse wheel. In touch devices rotation is done
 * by tap-and-move, selection by tap-and-hold and zoom by pinch.
 *
 * If no axes are set explicitly to Q3DBars, temporary default axes with no labels are created.
 * These default axes can be modified via axis accessors, but as soon any axis is set explicitly
 * for the orientation, the default axis for that orientation is destroyed.
 *
 * Q3DBarsNG supports more than one series visible at the same time. It is not necessary for all series
 * to have the same amount of rows and columns.
 * Row and column labels are taken from the first added series, unless explicitly defined to
 * row and column axes.
 *
 * \section1 How to construct a minimal Q3DBarsNG graph
 *
 * First, construct an instance of Q3DBars. Since we are running the graph as top level window
 * in this example, we need to clear the \c Qt::FramelessWindowHint flag, which gets set by
 * default:
 *
 * \snippet doc_src_q3dbars_construction.cpp 4
 *
 * After constructing Q3DBars, you can set the data window by changing the range on the row and
 * column axes. It is not mandatory, as data window will default to showing all of the data in
 * the series. If the amount of data is large, it is usually preferable to show just a
 * portion of it. For the example, let's set the data window to show first five rows and columns:
 *
 * \snippet doc_src_q3dbars_construction.cpp 0
 *
 * Now Q3DBarsNG is ready to receive data to be rendered. Create a series with one row of 5 values:
 *
 * \snippet doc_src_q3dbars_construction.cpp 1
 *
 * \note We set the data window to 5 x 5, but we are adding only one row of data. This is ok,
 * the rest of the rows will just be blank.
 *
 * Finally you will need to set it visible:
 *
 * \snippet doc_src_q3dbars_construction.cpp 2
 *
 * The complete code needed to create and display this graph is:
 *
 * \snippet doc_src_q3dbars_construction.cpp 3
 *
 * And this is what those few lines of code produce:
 *
 * \image q3dbars-minimal.png
 *
 * The scene can be rotated, zoomed into, and a bar can be selected to view its value,
 * but no other interaction is included in this minimal code example. You can learn more by
 * familiarizing yourself with the examples provided, like the \l{Bars Example}.
 *
 * \sa Q3DScatter, Q3DSurface, {Qt Graphs C++ Classes}
 */

/*!
 * Constructs a new 3D bar graph with optional \a parent window
 * and surface \a format.
 */

/*!
 * Destroys the 3D bar graph.
 */

/*!
 * \property Q3DBars::primarySeries
 *
 * \brief The primary series of the graph.
 */

/*!
 * Sets \a series as the primary series of the graph. The primary series
 * determines the row and column axis labels when the labels are not explicitly
 * set to the axes.
 *
 * If the specified series is not yet added to the graph, setting it as the
 * primary series will also implicitly add it to the graph.
 *
 * If the primary series itself is removed from the graph, this property
 * resets to default.
 *
 * If \a series is null, this property resets to default.
 * Defaults to the first added series or zero if no series are added to the graph.
 */

/*!
 * Adds the \a series to the graph. A graph can contain multiple series, but only one set of axes,
 * so the rows and columns of all series must match for the visualized data to be meaningful.
 * If the graph has multiple visible series, only the primary series will
 * generate the row or column labels on the axes in cases where the labels are not explicitly set
 * to the axes. If the newly added series has specified a selected bar, it will be highlighted and
 * any existing selection will be cleared. Only one added series can have an active selection.
 *
 * \sa seriesList(), primarySeries, QAbstract3DGraphNG::hasSeries()
 */

/*!
 * Removes the \a series from the graph.
 *
 * \sa QAbstract3DGraphNG::hasSeries()
 */

/*!
 * Inserts the \a series into the position \a index in the series list.
 * If the \a series has already been added to the list, it is moved to the
 * new \a index.
 * \note When moving a series to a new \a index that is after its old index,
 * the new position in list is calculated as if the series was still in its old
 * index, so the final index is actually the \a index decremented by one.
 *
 * \sa addSeries(), seriesList(), QAbstract3DGraphNG::hasSeries()
 */

/*!
 * Returns the list of series added to this graph.
 *
 * \sa QAbstract3DGraphNG::hasSeries()
 */

/*!
 * \property Q3DBars::multiSeriesUniform
 *
 * \brief Whether bars are to be scaled with proportions set to a single series
 * bar even if there are multiple series displayed.
 *
 * If set to \c {true}, \l{barSpacing}{bar spacing} will be correctly applied
 * only to the X-axis. Preset to \c false by default.
 */

/*!
 * \property Q3DBars::barThickness
 *
 * \brief The bar thickness ratio between the X and Z dimensions.
 *
 * The value \c 1.0 means that the bars are as wide as they are deep, whereas
 *\c 0.5 makes them twice as deep as they are wide. Preset to \c 1.0 by default.
 */

/*!
 * \property Q3DBars::barSpacing
 *
 * \brief Bar spacing in the X and Z dimensions.
 *
 * Preset to \c {(1.0, 1.0)} by default. Spacing is affected by the
 * barSpacingRelative property.
 *
 * \sa barSpacingRelative, multiSeriesUniform, barSeriesMargin
 */

/*!
 * \property Q3DBars::barSpacingRelative
 *
 * \brief Whether spacing is absolute or relative to bar thickness.
 *
 * If it is \c true, the value of \c 0.0 means that the bars are placed
 * side-to-side, \c 1.0 means that a space as wide as the thickness of one bar
 * is left between the bars, and so on. Preset to \c true.
 */

/*!
 * \property Q3DBars::barSeriesMargin
 * \since 6.3
 *
 * \brief Margin between series columns in X and Z dimensions.
 * Sensible values are on the range [0,1).
 *
 * Preset to \c {(0.0, 0.0)} by default. This property enables
 * showing bars from different series side by side, but with space between columns.
 *
 * \sa barSpacing
 */

/*!
 * \property Q3DBars::rowAxis
 *
 * \brief The axis attached to the active row.
 */

/*!
 * Sets the axis of the active row to \a axis. Implicitly calls addAxis() to
 * transfer the ownership of the axis to this graph.
 *
 * If \a axis is null, a temporary default axis with no labels is created.
 * This temporary axis is destroyed if another axis is set explicitly to the
 * same orientation.
 *
 * \sa addAxis(), releaseAxis()
 */

/*!
 * \property Q3DBars::columnAxis
 *
 * \brief The axis attached to the active column.
 */

/*!
 * Sets the axis of the active column to \a axis. Implicitly calls addAxis() to
 * transfer the ownership of the axis to this graph.
 *
 * If \a axis is null, a temporary default axis with no labels is created.
 * This temporary axis is destroyed if another axis is set explicitly to the
 * same orientation.
 *
 * \sa addAxis(), releaseAxis()
 */

/*!
 * \property Q3DBars::valueAxis
 *
 * Sets the active value axis (the Y-axis) to \a axis. Implicitly calls
 * addAxis() to transfer the ownership of \a axis to this graph.
 *
 * If \a axis is null, a temporary default axis with no labels and
 * an automatically adjusting range is created.
 * This temporary axis is destroyed if another axis is set explicitly to the
 * same orientation.
 *
 * \sa addAxis(), releaseAxis()
 */

/*!
 * \property Q3DBars::selectedSeries
 *
 * \brief The selected series or a null value.
 *
 * If selectionMode has the \c SelectionMultiSeries flag set, this
 * property holds the series that owns the selected bar.
 */

/*!
 * \property Q3DBars::floorLevel
 *
 * \brief The floor level for the bar graph in Y-axis data coordinates.
 *
 * The actual floor level will be restricted by the Y-axis minimum and maximum
 * values.
 * Defaults to zero.
 */

/*!
 * Adds \a axis to the graph. The axes added via addAxis are not yet taken to use,
 * addAxis is simply used to give the ownership of the \a axis to the graph.
 * The \a axis must not be null or added to another graph.
 *
 * \sa releaseAxis(), setValueAxis(), setRowAxis(), setColumnAxis()
 */

/*!
 * Releases the ownership of the \a axis back to the caller, if it is added to this graph.
 * If the released \a axis is in use, a new default axis will be created and set active.
 *
 * If the default axis is released and added back later, it behaves as any other axis would.
 *
 * \sa addAxis(), setValueAxis(), setRowAxis(), setColumnAxis()
 */

/*!
 * Returns the list of all added axes.
 *
 * \sa addAxis()
 */

Q3DBarsNG::Q3DBarsNG() : QAbstract3DGraphNG()
{
    QQmlComponent *component = new QQmlComponent(engine(), this);
    component->setData("import QtQuick; import QtGraphs; Bars3DNG { anchors.fill: parent; }", QUrl());
    d_ptr.reset(qobject_cast<QQuickDataVisBars *>(component->create()));
    setContent(component->url(), component, d_ptr.data());
}

Q3DBarsNG::~Q3DBarsNG()
{
}

void Q3DBarsNG::setPrimarySeries(QBar3DSeries *series)
{
    dptr()->setPrimarySeries(series);
    emit primarySeriesChanged(series);
}

QBar3DSeries *Q3DBarsNG::primarySeries() const
{
    return dptrc()->primarySeries();
}

void Q3DBarsNG::addSeries(QBar3DSeries *series)
{
    dptr()->addSeries(series);
}

void Q3DBarsNG::removeSeries(QBar3DSeries *series)
{
    dptr()->removeSeries(series);
}

void Q3DBarsNG::insertSeries(int index, QBar3DSeries *series)
{
    dptr()->insertSeries(index, series);
}

QList<QBar3DSeries *> Q3DBarsNG::seriesList() const
{
    return dptrc()->m_barsController->barSeriesList();
}

void Q3DBarsNG::setMultiSeriesUniform(bool uniform)
{
    dptr()->setMultiSeriesUniform(uniform);
    emit multiSeriesUniformChanged(uniform);
}

bool Q3DBarsNG::isMultiSeriesUniform() const
{
    return dptrc()->isMultiSeriesUniform();
}

void Q3DBarsNG::setBarThickness(float thicknessRatio)
{
    dptr()->setBarThickness(thicknessRatio);
    emit barThicknessChanged(thicknessRatio);
}

float Q3DBarsNG::barThickness() const
{
    return dptrc()->barThickness();
}

void Q3DBarsNG::setBarSpacing(const QSizeF &spacing)
{
    dptr()->setBarSpacing(spacing);
    emit barSpacingChanged(spacing);
}

QSizeF Q3DBarsNG::barSpacing() const
{
    return dptrc()->barSpacing();
}

void Q3DBarsNG::setBarSpacingRelative(bool relative)
{
    dptr()->setBarSpacingRelative(relative);
    emit barSpacingRelativeChanged(relative);
}

bool Q3DBarsNG::isBarSpacingRelative() const
{
    return dptrc()->isBarSpacingRelative();
}

void Q3DBarsNG::setBarSeriesMargin(const QSizeF &margin)
{
    dptr()->setBarSeriesMargin(margin);
    emit barSeriesMarginChanged(margin);
}

QSizeF Q3DBarsNG::barSeriesMargin() const
{
    return dptrc()->barSeriesMargin();
}

void Q3DBarsNG::setRowAxis(QCategory3DAxis *axis)
{
    dptr()->setRowAxis(axis);
    emit rowAxisChanged(axis);
}

QCategory3DAxis *Q3DBarsNG::rowAxis() const
{
    return dptrc()->rowAxis();
}

void Q3DBarsNG::setColumnAxis(QCategory3DAxis *axis)
{
    dptr()->setColumnAxis(axis);
    emit columnAxisChanged(axis);
}

QCategory3DAxis *Q3DBarsNG::columnAxis() const
{
    return dptrc()->columnAxis();
}

void Q3DBarsNG::setValueAxis(QValue3DAxis *axis)
{
    dptr()->setValueAxis(axis);
    emit valueAxisChanged(axis);
}

QValue3DAxis *Q3DBarsNG::valueAxis() const
{
    return dptrc()->valueAxis();
}

QBar3DSeries *Q3DBarsNG::selectedSeries() const
{
    return dptrc()->selectedSeries();
}

void Q3DBarsNG::setFloorLevel(float level)
{
    dptr()->setFloorLevel(level);
    emit floorLevelChanged(level);
}

float Q3DBarsNG::floorLevel() const
{
    return dptrc()->floorLevel();
}

void Q3DBarsNG::addAxis(QAbstract3DAxis *axis)
{
    dptr()->m_barsController->addAxis(axis);
}

void Q3DBarsNG::releaseAxis(QAbstract3DAxis *axis)
{
    dptr()->m_barsController->releaseAxis(axis);
}

QList<QAbstract3DAxis *> Q3DBarsNG::axes() const
{
    return dptrc()->m_barsController->axes();
}

bool Q3DBarsNG::isReflection() const
{
    return dptrc()->isReflection();
}

void Q3DBarsNG::setReflection(bool reflection)
{
    dptr()->setReflection(reflection);
    emit reflectionChanged(reflection);
}

QQuickDataVisBars *Q3DBarsNG::dptr()
{
    return static_cast<QQuickDataVisBars *>(d_ptr.data());
}

const QQuickDataVisBars *Q3DBarsNG::dptrc() const
{
    return static_cast<const QQuickDataVisBars *>(d_ptr.data());
}

QT_END_NAMESPACE
