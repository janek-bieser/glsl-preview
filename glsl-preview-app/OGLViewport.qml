import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

import GLRendering 1.0

Item {

    id: root
    property alias uniformModel: viewport.uniformModel

    signal error(string messageText);
    signal info(string messageText);

    Rectangle {
        id: viewportTools

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right

        border.width: 1
        anchors.topMargin: -1
        anchors.rightMargin: -1
        anchors.leftMargin: -1

        height: 36

        color: "#f3f3f3"

        Label {
            id: modelLbl
            text: "Model"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 12
        }

        ComboBox {
            property int lastIndex: 0
            property int selectedModelIndex: 0

            anchors.left: modelLbl.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 12

            model: ListModel {
                id: meshModel
                ListElement { text: "Plane" }
                ListElement { text: "Cube" }
                ListElement { text: "Load Custom..." }
            }

            onCurrentIndexChanged: {
                if (currentIndex == meshModel.count-1) {
                    console.log("load custom model");
                    currentIndex = lastIndex;
                    modelPicker.open();
                } else {
                    lastIndex = currentIndex;
                    selectedModelIndex = currentIndex;
                }
            }

            onSelectedModelIndexChanged: {
                var modelData = meshModel.get(selectedModelIndex);
                var meshData = { name: modelData.text };
                if (modelData.path) {
                    meshData.path = modelData.path;
                }
                viewport.selectModel(meshData);
            }

            FileDialog {
                id: modelPicker
                selectFolder: false
                selectMultiple: false

                nameFilters: ["Wavefront OBJ Files (*.obj *.OBJ)"]

                onSelectionAccepted: {
                    var path = fileUrl.toString();
                    if (path.indexOf("file://") == 0) {
                        path = path.substring(7);
                    }
                    var name = path.substring(path.lastIndexOf("/")+1);

                    var exists = false;
                    for (var i = 0; i < meshModel.count-1 && !exists; i++) {
                        var item = meshModel.get(i);
                        if (item.path == path) {
                            exists = true;
                        }
                    }

                    if (!exists) {
                        meshModel.insert(meshModel.count-1, { text: name, path: path });
                    } else {
                        console.log("model is already loaded");
                    }
                }
            }
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

    Item {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: viewportTools.bottom
        anchors.bottom: parent.bottom

        transform: Scale {
            yScale: -1
            origin.y: viewport.height / 2
        }

        GLViewport {
            id: viewport
            anchors.fill: parent
            onMessage: {
                if (type == "error") {
                    root.error(messageText);
                } else if (type == "info") {
                    root.info(messageText);
                }
            }
        }
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

    function reloadShaders() {
        console.log("reload shaders");
        viewport.reloadProgram();
    }

    function updateUniform(uniform) {
        viewport.updateUniform(uniform);
    }
}

