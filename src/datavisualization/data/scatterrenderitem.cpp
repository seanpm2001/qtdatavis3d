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

#include "scatterrenderitem_p.h"
#include "scatter3drenderer_p.h"
#include "qscatterdataproxy.h"

namespace QtDataVisualization {

/*!
 * \class QtDataVisualization::ScatterRenderItem
 * \internal
 */

/*!
 * \typedef ScatterRenderItemArray
 * \internal
 */

ScatterRenderItem::ScatterRenderItem()
    : AbstractRenderItem(),
      m_visible(false)
{
}

ScatterRenderItem::ScatterRenderItem(const ScatterRenderItem &other)
    : AbstractRenderItem(other),
      m_visible(false)
{
    m_position = other.m_position;
}

ScatterRenderItem::~ScatterRenderItem()
{
}

}
