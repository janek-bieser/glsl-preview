import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

RowLayout {
    id: root

    property var labels: ["x", "y", "z", "w"]
    property var defaultValues: [0, 0, 0, 1]

    property int numOfComponents: 4
    property real maxValue: 1000
    property real minValue: -1000

    signal valueChanged();

    anchors.left: parent.left
    anchors.right: parent.right

    spacing: 10

    function getComponents() {
        var c = [];
        for (var i = 0; i < root.children.length; i++) {
            var child = root.children[i];
            c.push(child.value);
        }
        return c;
    }

    function setComponents(c) {
        for (var i = 0; i < root.children.length && i < c.length; i++) {
            var child = root.children[i];
            child.value = c[i];
        }
    }

    Component.onCompleted: {
        var cmp = Qt.createComponent("LabeledNumberInput.qml");

        for (var i = 0; i < numOfComponents; i++) {
            var lni = cmp.createObject(root, { "label": labels[i] });
            lni.valueChanged.connect(root.valueChanged);
            lni.maxValue = root.maxValue;
            lni.minValue = root.minValue;
            lni.value = defaultValues[i];
        }
    }
}

