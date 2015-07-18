import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

Item {
    id: root

    property alias color: colorDisplay.color

    Image {
        anchors.fill: parent
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        source: "images/checker_bg.svg"
        fillMode: Image.Tile
        sourceSize.width: 25
        sourceSize.height: 25
    }

    Rectangle {
        id: colorDisplay
        anchors.fill: parent
        border.width: 1
        color: "black"
        radius: 5
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            picker.color = root.color
            picker.open();
        }
    }

    ColorDialog {
        id: picker
        onCurrentColorChanged: {
            root.color = currentColor;
        }
        showAlphaChannel: true
    }
}

