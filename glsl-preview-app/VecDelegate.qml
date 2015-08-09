import QtQuick 2.4

Rectangle {
    height: 80
    color: "#f3f3f3"

    LabeledVectorInput {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 12
        label: modelData.name
        numOfComponents: {
            var match = modelData.type.match(/^vec(1|2|3|4)$/);
            return match[1];
        }

        onValueChanged: {
            var c = getComponents();
            root.uniformChanged({name: modelData.name, values: c, type: modelData.type});
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

