import QtQuick 2.4
import QtQuick.Layouts 1.1

Item {
    height: 108

    anchors.left: parent.left
    anchors.right: parent.right

    property var uniformCache

    ColorInput {
        id: colorInput
        label: modelData.name
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 12
        onColorChanged: {
            var c = getComponents();
            uniformCache.setValue(modelData.name, {value: c, type: "vec4"});
            root.uniformChanged({name: modelData.name, values: c, type: "vec4"});
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
            colorInput.setComponents(value.value);
        }
    }
}

