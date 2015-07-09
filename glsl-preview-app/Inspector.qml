import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    color: "lightgray"

    SplitView {

        anchors.fill: parent
        orientation: Qt.Vertical

        handleDelegate: Rectangle {
            height: 28
            color: "#888"
            Text {
                anchors.centerIn: parent
                text: "Builtins"
            }
        }

        Item {
            Layout.fillHeight: true

            Rectangle {
                id: uniformsHeader

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: 28

                color: "#888"

                Text {
                    anchors.centerIn: parent
                    text: "Uniforms"
                }
            }

            ScrollView {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: uniformsHeader.bottom
                anchors.topMargin: 10

                ListView {
                    model: ListModel {
                        ListElement {}
                    }
                    delegate: Rectangle {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 12
                        LabeledVectorInput {
                            label: "LightPosition"
                            numOfComponents: 3
                        }
                    }
                }
            }
        }

        Rectangle {
            height: 100

            ScrollView {
                anchors.fill: parent

                ListView {
                    model: ListModel {
                        ListElement { name: "slp_Vertex"; type: "vec3"; category: "Attributes" }
                        ListElement { name: "slp_Normal"; type: "vec3"; category: "Attributes" }

                        ListElement { name: "slp_ModelMatrix"; type: "mat4"; category: "Uniforms" }
                        ListElement { name: "slp_ViewMatrix"; type: "mat4"; category: "Uniforms" }
                        ListElement { name: "slp_ProjectionMatrix"; type: "mat4"; category: "Uniforms" }
                        ListElement { name: "slp_NormalMatrix"; type: "mat4"; category: "Uniforms" }
                    }

                    delegate: Item {
                        height: 20
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 12
                        Text {
                            text: name + " : " + type
                        }
                    }

                    section.property: "category"
                    section.delegate: Item {
                        height: 24
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 12
                        Text {
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

