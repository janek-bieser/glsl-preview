import QtQuick 2.0
import QtQuick.Controls.Styles 1.2

TextAreaStyle {
    frame: Item{}
    handle: Item {
        implicitWidth: 14
        Rectangle {
            anchors.fill: parent
            color: (styleData.pressed || styleData.hovered) ? "#aaaaaa" : "#cccccc"
            anchors.rightMargin: 2
            anchors.leftMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            anchors.horizontalCenter: parent.horizontalCenter
            radius: 7
        }
        visible: control.height > 40
    }
    incrementControl: Item {}
    decrementControl: Item {}
    scrollBarBackground: Item {
        implicitWidth: 14
        implicitHeight: 26
    }
    backgroundColor: "#eeeeee"
}

