import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    property alias value: numInput.value
    property alias maxValue: numInput.maxValue
    property alias minValue: numInput.minValue

    property alias label: lbl.text

    implicitHeight: numInput.implicitHeight

    Layout.minimumWidth: 80
    Layout.alignment: Qt.AlignHCenter

    Label {
        id: lbl;
        text: label
        color: "#d6d6d6"
        anchors.verticalCenter: parent.verticalCenter
    }

    NumberInput {
        anchors.left: lbl.right
        anchors.leftMargin: 4
        anchors.right: parent.right
        id: numInput
    }
}

