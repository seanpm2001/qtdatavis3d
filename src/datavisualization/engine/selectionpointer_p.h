/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

#ifndef SELECTIONPOINTER_P_H
#define SELECTIONPOINTER_P_H

#include "q3dscene.h"
#include "datavisualizationglobal_p.h"
#include "surface3dcontroller_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class ShaderHelper;
class ObjectHelper;
class SurfaceObject;
class TextureHelper;
class Drawer;

class SelectionPointer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit SelectionPointer(Drawer *drawer);
    ~SelectionPointer();

    void render(GLuint defaultFboHandle = 0);
    void setPosition(const QVector3D &position);
    void setLabel(const QString &label);
    void setPointerObject(ObjectHelper *object);
    void handleDrawerChange();
    void updateBoundingRect(const QRect &rect);
    void updateScene(Q3DScene *scene);
    void updateSliceData(bool sliceActivated, GLfloat autoScaleAdjustment);
    void setHighlightColor(const QVector3D &colorVector);
    void setRotation(const QQuaternion &rotation);

private:
    void initializeOpenGL();
    void initShaders();
    void loadLabelMesh();

private:
    ShaderHelper *m_labelShader;
    ShaderHelper *m_pointShader;
    ObjectHelper *m_labelObj;
    ObjectHelper *m_pointObj; // Not owned
    TextureHelper *m_textureHelper;
    Q3DTheme *m_cachedTheme;
    bool m_labelBackground;
    LabelItem m_labelItem;
    Drawer *m_drawer;
    QRect m_mainViewPort;
    QVector3D m_position;
    Q3DScene *m_cachedScene;
    QString m_label;
    bool m_cachedIsSlicingActivated;
    GLfloat m_autoScaleAdjustment;
    QVector3D m_highlightColor;
    QQuaternion m_rotation;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
