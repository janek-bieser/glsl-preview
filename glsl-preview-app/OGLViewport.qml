import QtQuick 2.4
import QtQuick.Controls 1.3

Rectangle {
    color: "#454545"

    function loadShader(shaderFiles) {
        console.log("loading: " + shaderFiles.vertex + ", " + shaderFiles.fragment);
    }
}

