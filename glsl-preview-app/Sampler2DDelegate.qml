import QtQuick 2.4

Rectangle {
    color: "#f3f3f3"
    height: 80

    Sampler2DInput {
        label: modelData.name
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 12

        onImgSourceChanged: {
            var values = [imgSource];
            root.uniformChanged({name: modelData.name, values: values, type: "sampler2D"});
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
