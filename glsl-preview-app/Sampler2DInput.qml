import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

RowLayout {

    property alias label: lbl.text
    property string imgSource: ""

    id: root

    spacing: 12

    Rectangle {
        id: rect
        color: "grey"

        Layout.minimumHeight: parent.height
        Layout.minimumWidth: parent.height

        border.width: 1

        Image {
            id: thumbnail
            anchors.fill: parent
            anchors.margins: 1
            source: (root.imgSource.length > 0) ? "file://" + root.imgSource : ""
        }
    }

    ColumnLayout {

        Layout.fillWidth: true

        Label {
            id: lbl
        }

        RowLayout {
            anchors.right: parent.right
            anchors.left: parent.left

            TextField {
                id: imgPathInput
                Layout.fillWidth: true

                onAccepted: {
                    root.imgSource = text;
                }
            }

            Button {
                text: qsTr("Browse");
                onClicked: _fileDialog.open()
            }
        }
    }

    FileDialog {
        id: _fileDialog
        selectFolder: false
        selectMultiple: false

        nameFilters: ["Image Files (*.png *.PNG)"]

        onSelectionAccepted: {
            var path = img.substring(7, img.length);
            root.imgSource = img.substring(7, img.length);
        }
    }

    onImgSourceChanged: {
        imgPathInput.text = imgSource;
    }
}
