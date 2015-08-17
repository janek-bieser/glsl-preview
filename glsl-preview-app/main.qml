import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import QtGraphicalEffects 1.0

ApplicationWindow {
    id: window

    title: qsTr("GLSL Preview")
    width: 900
    height: 600

    visible: false

    minimumWidth: 850
    minimumHeight: 500

    menuBar: MenuBar {
        Menu {
            title: "&GLSL Preview"
            MenuItem {
                text: "&About GLSL Preview"
                onTriggered: console.log("Show About")
            }
        }

        Menu {
            title: qsTr("&Program")
            MenuItem {
                text: "&Build Program"
                onTriggered: {
                    debugConsole.text = "";
                    glViewport.reloadShaders();
                }
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
                text: shaderInspector.hidden ? qsTr("&Show Inspector") : qsTr("&Hide Inspector")
                onTriggered: shaderInspector.toggleHidden()
                shortcut: "Ctrl+i"
            }
            MenuItem {
                text: consoleContainer.hidden ? qsTr("&Show Console") : qsTr("&Hide Console")
                onTriggered: consoleContainer.toggleHidden()
                shortcut: "Ctrl+k"
            }
        }

        Menu {
            title: qsTr("&Help")
            MenuItem {
                text: qsTr("&User Manual")
            }
            MenuItem {
                text: qsTr("&Contact Support...")
            }
        }
    }

    Inspector {
        id: shaderInspector

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: 375

        uniformModel: glViewport.uniformModel

        onUniformChanged: {
            glViewport.updateUniform(uniform);
        }
    }

    Rectangle {
        id: divider
        color: "black"
        width: 1
        anchors.left: shaderInspector.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    SplitView {

        orientation: Qt.Vertical

        anchors.left: divider.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        handleDelegate: Rectangle {
            id: viewportConsoleDivider
            height: 12
            color: "#d5d5d5"

            border.width: 1
            border.color: "#646464"
            anchors.margins: -1
            anchors.left: parent.left
            anchors.right: parent.right
        }


        OGLViewport {
            id: glViewport

            Layout.fillHeight: true
            Layout.minimumHeight: 100

            anchors.left: parent.left
            anchors.right: parent.right

            onError: {
                debugConsole.appendError(messageText);
                consoleContainer.show();
            }

            onInfo: {
                debugConsole.appendInfo(messageText);
            }

            //ShaderSelectionMenu {
            //    id: shaderMenu
            //    anchors.centerIn: glViewport

            //    radius: 5

            //    onFilesSelected: {
            //        glViewport.loadShader(sources);
            //    }
            //}
        }

        Item {
            anchors.left: parent.left
            anchors.right: parent.right

            id: consoleContainer
            property real _goalHeight: 0
            property real _lastHeight: 100
            property bool hidden: height == 0

            function toggleHidden() {
                if (height > 0) {
                    _lastHeight = height;
                    _goalHeight = 0;
                } else {
                    _goalHeight = _lastHeight >= 100 ? _lastHeight : 100;
                }

                anim.start();
            }

            function show() {
                if (hidden) {
                    toggleHidden();
                }
            }

            transitions: [
                Transition {
                    NumberAnimation {
                        duration: 150
                        easing.type: Easing.OutCubic
                        properties: "height"
                    }
                }

            ]

            NumberAnimation on height {
                id: anim
                running: false
                from: consoleContainer.height
                to: consoleContainer._goalHeight
                duration: 220
                easing.type: Easing.InOutQuad
            }

            TextArea {
                id: debugConsole

                anchors.fill: parent
                anchors.margins: -1
                textMargin: 8
                textFormat: TextEdit.RichText
                backgroundVisible: true
                readOnly: true
                textColor: "#222"

                function appendError(msg) {
                    var fullMsg = "<p style='margin: 2 0;'><span style='color: red;'>Error :</span> " +
                            msg + "</p>";
                    debugConsole.append(fullMsg);
                }

                function appendInfo(msg) {
                    debugConsole.append("<p style='margin: 2 0;'><span style='color: #385;'>Info :</span> " + msg + "</p>");
                }
            }
        }

    }

}










