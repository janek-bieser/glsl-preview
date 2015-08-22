import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2

RowLayout {

    property alias label: lbl.text
    property string imgSource: ""
    signal reloadTexture()

    id: root

    spacing: 12

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
    }

    Rectangle {
        id: rect
        color: "#dedede"

        Layout.minimumHeight: parent.height
        Layout.minimumWidth: parent.height

        border.width: 1

        Image {
            id: thumbnail
            anchors.fill: parent
            anchors.margins: 1
            source: root.imgSource.length > 0 ? "file://" + root.imgSource : ""
        }

        Button {
            anchors.bottom: thumbnail.bottom
            anchors.bottomMargin: -5
            anchors.horizontalCenter: thumbnail.horizontalCenter
            text: qsTr("Select");
            onClicked: _fileDialog.open()
            width: 50
            height: 15
            style: ButtonStyle {
                label: Text {
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 10
                    text: control.text
                }
                background: Rectangle {
                    color: control.pressed ? "#71AEE3" : "#eee"
                    border.width: 1
                    border.color: "darkgrey"
                    radius: 3
                }
            }
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
