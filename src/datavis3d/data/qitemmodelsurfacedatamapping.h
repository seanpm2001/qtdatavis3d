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

#ifndef QITEMMODELSURFACEDATAMAPPING_H
#define QITEMMODELSURFACEDATAMAPPING_H

#include <QtDataVis3D/qdatavis3denums.h>
#include <QtDataVis3D/qabstractdatamapping.h>
#include <QStringList>

QT_DATAVIS3D_BEGIN_NAMESPACE

class QItemModelSurfaceDataMappingPrivate;

class QT_DATAVIS3D_EXPORT QItemModelSurfaceDataMapping : public QAbstractDataMapping
{
    Q_OBJECT
    Q_PROPERTY(QString rowRole READ rowRole WRITE setRowRole)
    Q_PROPERTY(QString columnRole READ columnRole WRITE setColumnRole)
    Q_PROPERTY(QString valueRole READ valueRole WRITE setValueRole)
    Q_PROPERTY(QStringList rowCategories READ rowCategories WRITE setRowCategories)
    Q_PROPERTY(QStringList columnCategories READ columnCategories WRITE setColumnCategories)

public:
    explicit QItemModelSurfaceDataMapping(QObject *parent = 0);
    QItemModelSurfaceDataMapping(const QString &valueRole, QObject *parent = 0);
    QItemModelSurfaceDataMapping(const QString &rowRole, const QString &columnRole,
                                 const QString &valueRole, const QStringList &rowCategories,
                                 const QStringList &columnCategories, QObject *parent = 0);
    virtual ~QItemModelSurfaceDataMapping();

    void setRowRole(const QString &role);
    QString rowRole() const;
    void setColumnRole(const QString &role);
    QString columnRole() const;
    void setValueRole(const QString &role);
    QString valueRole() const;

    void setRowCategories(const QStringList &categories);
    QStringList rowCategories() const;
    void setColumnCategories(const QStringList &categories);
    QStringList columnCategories() const;

    void remap(const QString &rowRole, const QString &columnRole,
               const QString &valueRole, const QStringList &rowCategories,
               const QStringList &columnCategories);

    Q_INVOKABLE int rowCategoryIndex(const QString& category);
    Q_INVOKABLE int columnCategoryIndex(const QString& category);

protected:
    QItemModelSurfaceDataMappingPrivate *dptr();
    const QItemModelSurfaceDataMappingPrivate *dptrc() const;

private:
    Q_DISABLE_COPY(QItemModelSurfaceDataMapping)
};

QT_DATAVIS3D_END_NAMESPACE

#endif
