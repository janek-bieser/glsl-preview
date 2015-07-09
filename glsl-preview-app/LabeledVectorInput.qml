import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ColumnLayout {
    property alias label: lbl.text
    property alias numOfComponents: vecInput.numOfComponents
    property alias vecLabels: vecInput.labels

    spacing: 8

    Label {
        id: lbl
        text: "Vector"
    }

    VectorInput {
        id: vecInput
    }
}

