import QtQuick 2.0
import QtQuick.Controls.Styles 1.2

ScrollViewStyle {
    handle: Item {
        implicitWidth: 14
        Rectangle {
            anchors.fill: parent
            color: (styleData.pressed || styleData.hovered) ? "#2B3238" : "#1F2429"
            anchors.leftMargin: 4
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
}

