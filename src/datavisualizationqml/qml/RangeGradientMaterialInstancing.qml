// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick3D
import QtQuick

CustomMaterial {
    property TextureInput custex: TextureInput {}

    shadingMode: CustomMaterial.Unshaded
    fragmentShader: "qrc:/shaders/fragmentrangegradientInstancing"
    vertexShader: "qrc:/shaders/vertexrangegradientInstancing"
}
