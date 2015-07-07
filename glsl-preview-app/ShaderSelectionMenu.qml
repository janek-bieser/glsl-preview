import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    signal filesSelected(var sources)

    width: 450
    height: 250

    color: "#f3f3f3"

    border.color: "black"
    border.width: 1

    Text {
        id: _header
        text: qsTr("Select your shader sources")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 15
        font.pointSize: 16
    }

    ColumnLayout {

        id: _inputs

        anchors.top: _header.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 25

        spacing: 20

        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            Label { text: "Vertex Shader" }
            FileInput { id: _vertexInput }
        }

        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            Label { text: "Fragment Shader" }
            FileInput { id: _fragmentInput }
        }
    }

    Button {
        text: "Ok"
        width: 80

        anchors.top: _inputs.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 30

        onClicked: {
            filesSelected( { vertex: _vertexInput.fileUrl, fragment: _fragmentInput.fileUrl } );
        }
    }
}

