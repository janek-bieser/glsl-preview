import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Dialog {
    id: root

    modality: Qt.WindowModal
    standardButtons: StandardButton.Cancel | StandardButton.Open

    width: 450
    Layout.minimumWidth: 450

    property alias vertexShader: vertexFileInput.fileUrl
    property alias fragmentShader: fragmentFileInput.fileUrl

    contentItem: Rectangle {
        implicitHeight: 200
        implicitWidth: 400
        color: "#eee"

        ColumnLayout {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10

            ColumnLayout {
                Label { text: "Vertex Shader" }
                FileInput {
                    id: vertexFileInput
                }
            }

            ColumnLayout {
                Label { text: "Fragment Shader" }
                FileInput {
                    id: fragmentFileInput
                }
            }

        }

        RowLayout {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 10

            Button {
                text: "Cancel"
                onClicked: root.close()
                implicitWidth: 90
            }

            Button {
                text: "OK"
                onClicked: {
                    root.accepted();
                    root.close();
                }

                implicitWidth: 90
            }
        }
    }
}

