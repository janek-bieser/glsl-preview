import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import QtGraphicalEffects 1.0

ApplicationWindow {
    id: window

    title: qsTr("GLSL Preview")
    width: 900
    height: 600
    visible: true

    minimumWidth: 800
    minimumHeight: 500

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Program")
            MenuItem {
                text: "&Build Program"
                onTriggered: console.log("build program")
                shortcut: "Ctrl+b"
            }
        }

        Menu {
            title: qsTr("&Window")
            MenuItem {
                text: qsTr("&Minimize")
                onTriggered: window.showMinimized()
                shortcut: "Ctrl+m"
            }
            MenuSeparator {}
            MenuItem {
                text: qsTr("&Toggle Inspector")
                onTriggered: (shaderInspector.width == 0) ? shaderInspector.width = 375 : shaderInspector.width = 0
                shortcut: "Ctrl+i"
            }
        }
    }

    Inspector {
        id: shaderInspector

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: 375
    }

    OGLViewport {
        id: glViewport

        anchors.left: shaderInspector.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        ShaderSelectionMenu {
            id: shaderMenu
            anchors.centerIn: parent

            radius: 5

            onFilesSelected: {
                console.log(sources.vertex, sources.fragment);
            }
        }
    }

}
