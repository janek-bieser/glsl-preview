import QtQuick 2.4

Rectangle {
    color: "#f3f3f3"
    height: 80

    property var uniformCache

    Sampler2DInput {
        id: imgInput
        label: modelData.name
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 12

        onImgSourceChanged: {
            var values = [imgSource];
            console.log(values);
            uniformCache.setValue(modelData.name, {value: imgSource, type: "sampler2D"});
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

    function readCachedValue() {
        var value = uniformCache.getValue(modelData.name);

        if (value && value.type === modelData.type) {
            imgInput.imgSource = value.value.toString();
        }
    }
}
