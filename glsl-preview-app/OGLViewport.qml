import QtQuick 2.4
import QtQuick.Controls 1.3

import GLRendering 1.0

Item {
    GLViewport {
        anchors.fill: parent
    }

    function loadShader(shaderFiles) {
        console.log("loading: " + shaderFiles.vertex + ", " + shaderFiles.fragment);
    }
}

