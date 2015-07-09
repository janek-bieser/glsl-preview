import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2

TextField {
    property real value: 0
    property real minValue: -1000
    property real maxValue: 1000

    validator: DoubleValidator {
        bottom: minValue
        top: maxValue
    }

    horizontalAlignment: TextInput.AlignRight

    text: "0.000"

    onTextChanged: {
        var temp = parseFloat(text) || 0;
        if (temp > maxValue) {
            temp = maxValue;
            text = temp.toFixed(3)
        } else if (temp < minValue) {
            temp = minValue;
            text = temp.toFixed(3)
        }

        value = temp;
    }

    onEditingFinished: {
        text = value.toFixed(3).toString();
    }

    onFocusChanged: {
        if (focus) {
            selectAll();
        }
    }

    style: TextFieldStyle {
        textColor: "#111"
        background: Rectangle {
            radius: 5
            implicitWidth: 100
            implicitHeight: 22
            border.width: 1
            border.color: "#555"
        }
    }
}
