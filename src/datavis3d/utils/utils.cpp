/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtDataVis3D module.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "utils_p.h"

#include <QVector3D>
#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QImage>

#include <qmath.h>

#include <QDebug>

QTCOMMERCIALDATAVIS3D_BEGIN_NAMESPACE

const float m_pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f;

QVector3D Utils::vectorFromColor(const QColor &color)
{
    return QVector3D(color.redF(), color.greenF(), color.blueF());
}

void Utils::printText(QPainter *painter, const QString &text, const QPoint &position
                      , bool absoluteCoords, qreal rotation, qreal scale)
{
    painter->save();
    painter->setCompositionMode(QPainter::CompositionMode_Source);
    // TODO: None of the commented-out stuff works..
    //painter->setBackgroundMode(Qt::OpaqueMode);
    //painter->setBackground(QBrush(d_ptr->m_textBackgroundColor));
    //painter->setBrush(QBrush(d_ptr->m_textBackgroundColor));
    //painter->setPen(d_ptr->m_textBackgroundColor);
    painter->setPen(Qt::black); // TODO: Use black, as nothing works
    QFont bgrFont = QFont(QStringLiteral("Arial"), 17);
    QFont valueFont = QFont(QStringLiteral("Arial"), 11);
    valueFont.setBold(true);
    painter->setFont(bgrFont);
    QFontMetrics valueFM(valueFont);
    QFontMetrics bgrFM(bgrFont);
    int valueStrLen = valueFM.width(text);
    int bgrStrLen = 0;
    int bgrHeight = valueFM.height() + 8;
    QString bgrStr = QString();
    do {
        bgrStr.append(QStringLiteral("I"));
        bgrStrLen = bgrFM.width(bgrStr);
    } while (bgrStrLen <= (valueStrLen + 8));
    //int bgrLen = valueStrLen + 10;
    //painter->drawRoundedRect(data->d_ptr->position().x() - (bgrLen / 2)
    //                         , data->d_ptr->position().y() - 30
    //                         , bgrLen, 30, 10.0, 10.0);
#if 0
    // Hack solution, as drawRect doesn't work
    painter->drawText(position.x() - (bgrStrLen / 2)
                      , position.y() - bgrHeight
                      , bgrStrLen, bgrHeight
                      , Qt::AlignCenter | Qt::AlignVCenter
                      , bgrStr);
    //painter->setPen(d_ptr->m_textColor);
    painter->setPen(Qt::lightGray); // TODO: Use lightGray, as nothing works
    painter->setFont(valueFont);
    painter->drawText(position.x() - (valueStrLen / 2)
                      , position.y() - bgrHeight
                      , valueStrLen, bgrHeight
                      , Qt::AlignCenter | Qt::AlignVCenter
                      , text);
#else
    //qDebug() << painter->window() << painter->viewport();
    painter->scale(scale, scale);
    if (absoluteCoords) {
        // This assumes absolute screen coordinates
        painter->translate(position.x() - (((float)bgrStrLen / 2.0f) * cos(rotation * m_pi / 180.0f))
                           + (((float)bgrHeight / 2.0f) * sin(rotation * m_pi / 180.0f))
                           , position.y()
                           - ((((float)bgrHeight / 2.0f) * cos(rotation * m_pi / 180.0f))
                              + (((float)bgrStrLen / 2.0f) * sin(rotation * m_pi / 180.0f))));
    } else {
        // This calculates y as a distance from screen bottom
        painter->translate(position.x() - (((float)bgrStrLen / 2) * cos(rotation * m_pi / 180.0f))
                           + (((float)bgrHeight / 2.0f) * sin(rotation * m_pi / 180.0f))
                           , painter->window().height() - position.y()
                           - ((((float)bgrHeight / 2.0f) * cos(rotation * m_pi / 180.0f))
                              + (((float)bgrStrLen / 2.0f) * sin(rotation * m_pi / 180.0f))));
    }
    //qDebug() << painter->window().height() - position.y()
    //            - ((((float)bgrHeight / 2.0f) * cos(rotation * m_pi / 180.0f))
    //               + (((float)bgrStrLen / 2.0f) * sin(rotation * m_pi / 180.0f)));
    painter->rotate(rotation);
    painter->drawText(0, 0
                      , bgrStrLen, bgrHeight
                      , Qt::AlignCenter | Qt::AlignVCenter
                      , bgrStr);
    painter->setPen(Qt::lightGray); // TODO: Use lightGray, as nothing works
    painter->setFont(valueFont);
    painter->drawText(6, 0
                      , valueStrLen, bgrHeight
                      , Qt::AlignCenter | Qt::AlignVCenter
                      , text);
    painter->resetTransform();
#endif
    painter->restore();
}

QImage Utils::printTextToImage(const QString &text, const QColor &bgrColor, const QColor &txtColor
                               , bool noBackground)
{
    // Calculate text dimensions
    QFont valueFont = QFont(QStringLiteral("Arial"), 11);
    valueFont.setBold(true);
    QFontMetrics valueFM(valueFont);
    int valueStrWidth = valueFM.width(text);
    int valueStrHeight = valueFM.height();
    QSize labelSize;
    if (noBackground)
        labelSize = QSize(valueStrWidth, valueStrHeight);
    else
        labelSize = QSize(valueStrWidth + 10, valueStrHeight + 10);

    // Create image
    QImage image = QImage(labelSize, QImage::Format_ARGB32);

    // Init painter
    QPainter painter(&image);
    // Paint text
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    if (noBackground) {
        painter.setBackgroundMode(Qt::OpaqueMode);
        painter.setBackground(Qt::transparent);
        painter.setBrush(Qt::transparent);
        painter.setFont(valueFont);
        painter.setPen(txtColor);
        painter.drawText(0, 0
                         , valueStrWidth, valueStrHeight
                         , Qt::AlignCenter | Qt::AlignVCenter
                         , text);
    } else {
        painter.setBrush(QBrush(bgrColor));
        painter.setPen(bgrColor);
        painter.drawRect(0, 0, labelSize.width(), labelSize.height());
        painter.setFont(valueFont);
        painter.setPen(txtColor);
        painter.drawText(5, 5
                         , valueStrWidth, valueStrHeight
                         , Qt::AlignCenter | Qt::AlignVCenter
                         , text);
    }
    return image;
}

QTCOMMERCIALDATAVIS3D_END_NAMESPACE
