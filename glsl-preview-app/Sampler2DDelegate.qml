import QtQuick 2.4

Item {
    height: 100

    property var uniformCache

    anchors.left: parent.left
    anchors.right: parent.right

    Sampler2DInput {
        id: imgInput
        label: modelData.name
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 12

        onImgSourceChanged: {
            var values = [imgSource];
            uniformCache.setValue(modelData.name, {value: imgSource, type: "sampler2D"});
            root.uniformChanged({name: modelData.name, values: values, type: "sampler2D"});
        }
        onReloadTexture: {
            var values = [imgSource];
            root.uniformChanged({name: modelData.name, values: values, type: "sampler2D"});
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 1
        color: "#2a3137"
    }

    function readCachedValue() {
        var value = uniformCache.getValue(modelData.name);

        if (value && value.type === modelData.type) {
            imgInput.imgSource = value.value.toString();
        }
    }
}
