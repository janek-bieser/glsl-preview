import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

import "UniformCache.js" as UniformCache

Rectangle {
    property alias uniformModel: uniformList.model

    signal uniformChanged(var uniform)

    id: root

    color: "#e3e3e3"

    SplitView {

        anchors.fill: parent
        orientation: Qt.Vertical

        handleDelegate: Rectangle {
            height: 28
            color: "#d5d5d5"

            border.width: 1
            anchors.margins: -1
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                anchors.centerIn: parent
                text: "Builtins"
                font.pointSize: 16
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

                color: "#d5d5d5"

                Text {
                    anchors.centerIn: parent
                    text: "Uniform Inspector"
                    font.pointSize: 16
                }
            }

            Component {
                id: vecComponent
                VecDelegate { width: propView.width; uniformCache: UniformCache }
            }

            Component {
                id: colorComponent
                ColorDelegate { width: propView.width; uniformCache: UniformCache }
            }

            Component {
                id: sampler2DComponent
                Sampler2DDelegate { width: propView.width; uniformCache: UniformCache }
            }

            Component {
                id: inspectorDelegate
                Loader {
                    property variant modelData: uniformList.model.get(index)
                    sourceComponent: {
                        if (/^vec(2|3)$/.test(type)) {
                            return vecComponent;
                        } else if (/^vec4$/.test(type)) {
                            if (name.match(/color/i)) {
                                return colorComponent;
                            } else {
                                return vecComponent;
                            }
                        } else if(type == "sampler2D") {
                            return sampler2DComponent
                        } else if (type == "float") {
                            modelData.type = "vec1";
                            return vecComponent;
                        }
                    }
                    function readCachedValue() {
                        if (item != null) {
                            item.readCachedValue();
                        }
                    }
                }
            }

            ScrollView {
                id: propView
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: uniformsHeader.bottom

                ListView {
                    id: uniformList
                    delegate: inspectorDelegate

                    onModelChanged: {
                        UniformCache.reset(model);

                        var len = uniformList.count;
                        var lastIdx = uniformList.currentIndex;
                        for (var i = 0; i < len; i++) {
                            uniformList.currentIndex = i;
                            uniformList.currentItem.readCachedValue();
                        }
                        uniformList.currentIndex = lastIdx;
                    }
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
                        ListElement { name: "slp_TexCoords (location=2)"; type: "vec2"; category: "Attributes" }

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

