import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ScrollView {
    //anchors.fill: parent

    ListView {
        model: ListModel {
            ListElement { name: "slp_Vertex (location=0)"; type: "vec3"; category: "Attributes" }
            ListElement { name: "slp_Normal (location=1)"; type: "vec3"; category: "Attributes" }
            ListElement { name: "slp_TexCoords (location=2)"; type: "vec2"; category: "Attributes" }

            ListElement { name: "slp_ModelMatrix"; type: "mat4"; category: "Uniforms" }
            ListElement { name: "slp_ViewMatrix"; type: "mat4"; category: "Uniforms" }
            ListElement { name: "slp_ProjectionMatrix"; type: "mat4"; category: "Uniforms" }
            ListElement { name: "slp_MVPMatrix"; type: "mat4"; category: "Uniforms" }
            ListElement { name: "slp_NormalMatrix"; type: "mat3"; category: "Uniforms" }
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

