import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

RowLayout {
    property alias fileUrl: _fileDialog.fileUrl

    anchors.left: parent.left
    anchors.right: parent.right

    TextField {
        id: _txt
        anchors.left: parent.left
        anchors.right: _btn.left
        anchors.rightMargin: 10
    }

    Button {
        id: _btn
        anchors.right: parent.right
        text: qsTr("Select...")
        onClicked: {
            _fileDialog.open();
        }
    }

    FileDialog {
        id: _fileDialog
        selectFolder: false
        selectMultiple: false

        nameFilters: ["Shader Source Code (*.glsl *.vertex *.fragment *.vert *.frag *.vs *.fs)"]

        onSelectionAccepted: {
            _txt.text = fileUrl.toString()
        }
    }
}
