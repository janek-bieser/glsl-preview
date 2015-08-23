import QtQuick 2.4

Item {
    height: 72

    property var uniformCache

    LabeledVectorInput {
        id: vecInput
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
            uniformCache.setValue(modelData.name, {value: c, type: "vec" + numOfComponents});
            root.uniformChanged({name: modelData.name, values: c, type: modelData.type});
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
            vecInput.setComponents(value.value);
        }
    }
}

