import QtQuick 2.0
import QtQuick.Controls.Styles 1.2

ButtonStyle {
    label: Text {
        renderType: Text.NativeRendering
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 11
        text: control.text
        color: "#d6d6d6"
    }
    background: Rectangle {
        color: control.pressed ? "#55677A" : "#495868"
        //border.width: 1
        //border.color: "#2a3137"
    }
}

