import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2

import "styles"

TextField {
    id: root
    property real value: 0
    property real minValue: -1000
    property real maxValue: 1000

    validator: DoubleValidator {}

    horizontalAlignment: TextInput.AlignRight

    onValueChanged: {
        text = value.toFixed(3);
    }

    onEditingFinished: {
        _setValue();
        text = value.toFixed(3);
    }

    onFocusChanged: {
        if (focus) {
            selectAll();
        }
    }

    function _setValue() {
        var tmp = parseFloat(text) || 0;
        tmp = validateValue(tmp);
        root.value = tmp;
    }

    style: SLPTextFieldStyle{}

    function validateValue(v) {
        if (v > maxValue) {
            v = maxValue;
        } else if (v < minValue) {
            v = minValue;
        }
        return v;
    }

    Component.onCompleted: {
        text = value.toFixed(3);
    }
}
