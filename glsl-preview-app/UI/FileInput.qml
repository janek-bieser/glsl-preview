import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

RowLayout {
    id: root
    property string fileUrl

    TextField {
        id: _txt
        Layout.fillWidth: true
        onTextChanged: {
            fileUrl = text;
        }
    }

    Button {
        id: _btn
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
