import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    color: "#dedede"

    SplitView {

        anchors.fill: parent
        orientation: Qt.Vertical

        handleDelegate: Rectangle {
            height: 28
            color: "#777"

            border.width: 1
            anchors.margins: -1
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                anchors.centerIn: parent
                text: "Builtins"
                font.pointSize: 16
                color: "#f3f3f3"
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.minimumHeight: 200

            Rectangle {
                id: uniformsHeader

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: 36

                border.width: 1
                anchors.margins: -1

                color: "#777"

                Text {
                    anchors.centerIn: parent
                    text: "Uniforms"
                    font.pointSize: 16
                    color: "#f3f3f3"
                }
            }

            ListModel {
                id: propsModel
                ListElement { name: "LightPosition"; componentCount: 3; type: "vec" }
                ListElement { name: "LightColor"; componentCount: 4; type: "color" }
                ListElement { name: "LightColor"; componentCount: 4; type: "color" }
            }

            Component {
                id: vecComponent

                Item {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 12
                    height: 80

                    LabeledVectorInput {
                        anchors.verticalCenter: parent.verticalCenter
                        label: modelData.name
                        numOfComponents: modelData.componentCount
                        onValueChanged: {
                            // update vec uniform
                        }
                    }
                }
            }

            Component {
                id: colorComponent

                Item {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 12
                    height: 106

                    ColorInput {
                        label: modelData.name
                        anchors.verticalCenter: parent.verticalCenter
                        onColorChanged: {
                            // update color uniform
                        }
                    }
                }
            }

            Component {
                id: inspectorDelegate
                Loader {
                    property variant modelData: propsModel.get(index);
                    sourceComponent: {
                        if (type == "vec") {
                            return vecComponent;
                        } else if (type == "color") {
                            return colorComponent;
                        }
                    }
                }
            }

            ScrollView {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: uniformsHeader.bottom

                ListView {
                    model: propsModel
                    delegate: inspectorDelegate
                }
            }
        }

        Item {
            height: 100

            ScrollView {
                anchors.fill: parent

                ListView {
                    model: ListModel {
                        ListElement { name: "slp_Vertex (location=0)"; type: "vec3"; category: "Attributes" }
                        ListElement { name: "slp_Normal (location=1)"; type: "vec3"; category: "Attributes" }

                        ListElement { name: "slp_ModelMatrix"; type: "mat4"; category: "Uniforms" }
                        ListElement { name: "slp_ViewMatrix"; type: "mat4"; category: "Uniforms" }
                        ListElement { name: "slp_ProjectionMatrix"; type: "mat4"; category: "Uniforms" }
                        ListElement { name: "slp_MVPMatrix"; type: "mat4"; category: "Uniforms" }

                        ListElement { name: "slp_NormalMatrix"; type: "mat4"; category: "Uniforms" }
                    }

                    delegate: Item {
                        height: 20
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 12

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: name
                        }
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            text: type
                            color: "#326545"
                        }
                    }

                    section.property: "category"
                    section.delegate: Item {
                        height: 28
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 12
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: section
                            font.bold: true
                            font.pointSize: 14
                        }
                    }
                }
            }
        }
    }
}

