import QtQuick 2.4

Rectangle {
    color: "#f3f3f3"
    height: 112

    ColorInput {
        label: modelData.name
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 12
        onColorChanged: {
            var c = getComponents();
            root.uniformChanged({name: modelData.name, values: c, type: "vec4"});
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 1
        color: "#999"
    }
}

