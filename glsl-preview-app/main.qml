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
                onTriggered: aboutDialog.open()
            }
        }

        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open Shader...")
                onTriggered: {
                    shaderDialog.open();
                }
                shortcut: "Ctrl+o"
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

    ShaderSelectionDialog {
        id: shaderDialog
        onAccepted: {
            var vs = vertexShader.toString();
            var fs = fragmentShader.toString();

            if (vs.indexOf("file://") >= 0) {
                vs = vs.substring(7);
            }
            if (fs.indexOf("file://") >= 0) {
                fs = fs.substring(7);
            }

            glViewport.loadShader({ vertex: vs, fragment: fs });
        }
    }

    Dialog {
        id: aboutDialog
        title: "About"
        modality: Qt.ApplicationModal
        contentItem: Rectangle {
            anchors.fill: parent
            color: "#eee"
            implicitWidth: 280
            implicitHeight: 340

            Item {
                width: parent.implicitWidth
                height: parent.implicitHeight
                anchors.centerIn: parent
                Image {
                    id: aboutImg
                    source: "images/cube_256.png"
                    width: 128
                    height: 128
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 20
                }

                Label {
                    id: aboutTitle
                    text: "GLSL Preview"
                    font.pointSize: 16
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: aboutImg.bottom
                }

                Label {
                    anchors.top: aboutTitle.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 24
                    textFormat: TextEdit.RichText
                    text: "<div style='text-align: center'><p>Concept<br/>Design<br/>Programming</p><p>by</p><p><strong>Janek Bieser</strong><br/>j.bieser@fh-bingen.de</p></div>"
                }
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
                font.family: "Monaco"
                font.pointSize: 11

                Connections {
                    target: Logger

                    onErrorMessage: {
                        debugConsole.appendError(message);
                        consoleContainer.show();
                    }

                    onInfoMessage: {
                        debugConsole.appendInfo(message);
                    }
                }

                function appendError(msg) {
                    var fullMsg = "<p style='margin: 2 0;'><span style='color: red;'>Error:</span> " +
                            msg + "</p>";
                    debugConsole.append(fullMsg);
                }

                function appendInfo(msg) {
                    debugConsole.append("<p style='margin: 2 0;'><span style='color: #385;'>Info:</span> " + msg + "</p>");
                }
            }
        }

    }

}










