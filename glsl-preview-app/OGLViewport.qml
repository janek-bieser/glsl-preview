import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2

import GLRendering 1.0
import "styles"

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
        border.color: "#1F2429"
        anchors.topMargin: -1
        anchors.rightMargin: -1
        anchors.leftMargin: -1

        height: 36

        color: "#343c44"

        Label {
            id: modelLbl
            text: "Model"
            color: "#d6d6d6"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 12
        }

        ComboBox {
            id: modelComboBox
            property int lastIndex: 0
            property int selectedModelIndex: 0

            style: ComboBoxStyle {
                background: Rectangle {
                    implicitWidth: 120
                    implicitHeight: 18
                    color: "#495868"
                    TriangleIcon {
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.rightMargin: 5
                        width: 10
                        height: width
                        flipped: true
                    }
                }
                label: Label {
                    id: _boxLbl
                    font.pointSize: 11
                    color: "#d6d6d6"
                    text: control.currentText.length < 17 ? control.currentText :  control.currentText.substring(0, 14) + "…";
                }
            }

            anchors.left: modelLbl.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 12

            model: ListModel {
                id: meshModel
                ListElement { text: "Plane" }
                ListElement { text: "Cube" }
                ListElement { text: "Load Custom…" }
            }

            onCurrentIndexChanged: {
                if (currentIndex == meshModel.count-1) {
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
                        //modelComboBox.selectedModelIndex(meshModel.count-1);
                        modelComboBox.currentIndex = meshModel.count-2;
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
            color: "#d6d6d6"
        }

        Rectangle {
            id: colorPickerRect
            anchors.right: parent.right
            height: 20
            width: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 12
            border.width: 1
            border.color: "#2a3137"
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
        viewport.loadShaders(shaderFiles.vertex, shaderFiles.fragment);
    }

    function reloadShaders() {
        viewport.reloadProgram();
    }

    function updateUniform(uniform) {
        viewport.updateUniform(uniform);
    }
}

