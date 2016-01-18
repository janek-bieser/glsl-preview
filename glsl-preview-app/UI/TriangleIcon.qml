import QtQuick 2.4

Item {
    property color iconColor: "#565656"
    property bool flipped: false

    implicitWidth: 20
    implicitHeight: 20

    Image {
        source: "images/triangle.svg"

        sourceSize.width: parent.width
        sourceSize.height: parent.height

        transform: Scale {
            yScale: flipped ? -1 : 1
            origin.y: flipped ? height / 2 : 0
        }
    }
}

