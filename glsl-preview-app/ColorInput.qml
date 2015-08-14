import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ColumnLayout {

    property alias label: vecInput.label
    property alias color: picker.color

    spacing: 10

    LabeledVectorInput {
        id: vecInput
        numOfComponents: 4
        vecLabels: ["r", "g", "b", "a"]

        minValue: 0
        maxValue: 1

        onValueChanged: {
            var c = vecInput.getComponents();
            var theColor = Qt.rgba(c[0], c[1], c[2], c[3]);
            picker.color = theColor;
        }
    }

    ColorPicker {
        id: picker

        width: 350
        height: 24

        onColorChanged: {
            vecInput.setComponents([color.r, color.g, color.b, color.a]);
        }
    }

    function getComponents() {
        return vecInput.getComponents();
    }

    function setComponents(c) {
        vecInput.setComponents(c);
    }

}

