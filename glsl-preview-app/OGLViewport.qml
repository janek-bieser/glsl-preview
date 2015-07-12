import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

import GLRendering 1.0

Item {

    Rectangle {
        id: borderLeft
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 1
        color: "black"
    }

    Rectangle {
        id: viewportTools

        anchors.left: borderLeft.right
        anchors.top: parent.top
        anchors.right: parent.right

        border.width: 1
        anchors.topMargin: -1
        anchors.rightMargin: -1
        anchors.leftMargin: -1

        height: 36

        Text {
            text: "OpenGL v" + viewport.glVersion
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 12
        }

        Text {
            anchors.right: colorPickerRect.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 5
            text: "Background Color"
        }

        Rectangle {
            id: colorPickerRect
            anchors.right: parent.right
            height: 20
            width: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 12
            border.width: 1
            color: "black"

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    colorPicker.open();
                }
            }
        }
    }

    GLViewport {
        id: viewport

        anchors.left: borderLeft.right
        anchors.right: parent.right
        anchors.top: viewportTools.bottom
        anchors.bottom: parent.bottom
    }

    ColorDialog {
        id: colorPicker
        onCurrentColorChanged: {
            colorPickerRect.color = currentColor;
            viewport.backgroundColor = currentColor;
        }
    }

    function loadShader(shaderFiles) {
        console.log("loading: " + shaderFiles.vertex + ", " + shaderFiles.fragment);
    }
}

