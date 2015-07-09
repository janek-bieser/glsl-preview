import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

RowLayout {
    id: root

    property var labels: ["x", "y", "z", "w"]
    property int numOfComponents: 4

    spacing: 10

    Component.onCompleted: {
        var cmp = Qt.createComponent("LabeledNumberInput.qml");

        for (var i = 0; i < numOfComponents; i++) {
            cmp.createObject(root, { "label": labels[i] });
        }
    }
}

