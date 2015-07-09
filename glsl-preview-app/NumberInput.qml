import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2

Item {
    property alias value: _numberField.value
    property alias minValue: _numberField.minValue
    property alias maxValue: _numberField.maxValue

    id: _numberInput

    implicitWidth: 100
    implicitHeight: 20

    Item {
        id: controlls

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 10

        TriangleIcon {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: parent.height / 2 - 1
        }

        TriangleIcon {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: parent.height / 2 - 1
            flipped: true
        }

        MouseArea {
            anchors.fill: parent

            cursorShape: Qt.SizeVerCursor

            property real curY: 0

            onMouseYChanged: {
                var diff = curY - mouseY;
                curY = mouseY;
                if (curY != 0) {
                    _numberInput.addAmount(diff);
                }
            }

            onPressed: {
                curY = mouseY;
            }
        }

    }

    NumberField {
        id: _numberField

        anchors.left: parent.left
        anchors.right: controlls.left
        anchors.rightMargin: 2
        anchors.verticalCenter: parent.verticalCenter

        Keys.onUpPressed: (event.modifiers & Qt.ShiftModifier) ? _numberInput.addAmount(10) : _numberInput.addAmount(1)
        Keys.onDownPressed: (event.modifiers & Qt.ShiftModifier) ? _numberInput.addAmount(-10) : _numberInput.addAmount(-1)
    }

    function addAmount(amount) {
        var tmp = _numberField.value + (amount * 0.01);
        if (tmp > maxValue) {
            tmp = maxValue;
        } else if (tmp < minValue) {
            tmp = minValue;
        }

        _numberField.text = tmp.toFixed(3).toString();
    }
}

