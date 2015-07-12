import QtQuick 2.4
import QtQuick.Controls 1.3

import GLRendering 1.0

Item {
    GLViewport {
        id: viewport
        anchors.fill: parent
    }

    Text {
        id: glVersionText
        text: "OpenGL v" + viewport.glVersion
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 12
    }

    function loadShader(shaderFiles) {
        console.log("loading: " + shaderFiles.vertex + ", " + shaderFiles.fragment);
    }
}

