import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2

import "styles"

RowLayout {

    property alias label: lbl.text
    property string imgSource: ""
    signal reloadTexture()

    id: root

    spacing: 12

    ColumnLayout {

        Layout.fillWidth: true
        spacing: 6

        Label {
            id: lbl
            color: "#d6d6d6"
        }

        RowLayout {
            anchors.right: parent.right
            anchors.left: parent.left

            TextField {
                id: imgPathInput
                Layout.fillWidth: true

                style: SLPTextFieldStyle{}

                onAccepted: {
                    if (root.imgSource == text) {
                        root.reloadTexture()

                        // TODO find a way to reaload Image
                        thumbnail.sourceChanged("file://" + root.imgSource);
                    } else {
                        root.imgSource = text;
                    }
                }
            }

        }

        Button {
            text: qsTr("Select");
            onClicked: _fileDialog.open()
            implicitWidth: 80
            style: SLPButtonStyle{}
        }
    }

    Rectangle {
        id: rect
        color: "#4a5259"

        Layout.minimumHeight: parent.height
        Layout.minimumWidth: parent.height

        border.width: 1
        border.color: "#2a3137"

        Image {
            id: thumbnail
            anchors.fill: parent
            anchors.margins: 1
            source: root.imgSource.length > 0 ? "file://" + root.imgSource : ""
        }

    }

    FileDialog {
        id: _fileDialog
        selectFolder: false
        selectMultiple: false

        nameFilters: ["Image Files (*.png *.PNG)"]

        onSelectionAccepted: {
            var img = fileUrl.toString();
            var path = img.substring(7, img.length);
            root.imgSource = path;
        }
    }

    onImgSourceChanged: {
        imgPathInput.text = root.imgSource;
    }
}
