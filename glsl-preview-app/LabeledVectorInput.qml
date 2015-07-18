import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ColumnLayout {
    id: root

    property alias label: lbl.text
    property alias numOfComponents: vecInput.numOfComponents
    property alias vecLabels: vecInput.labels
    property alias maxValue: vecInput.maxValue
    property alias minValue: vecInput.minValue

    signal valueChanged();

    spacing: 8

    anchors.left: parent.left
    anchors.right: parent.right

    Label {
        id: lbl
        text: "Vector"
        //font.bold: true
    }

    VectorInput {
        id: vecInput
        onValueChanged: {
            root.valueChanged();
        }
    }

    function getComponents() {
        return vecInput.getComponents();
    }

    function setComponents(c) {
        vecInput.setComponents(c);
    }
}

