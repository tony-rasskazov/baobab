import QtQuick 2.4

Row {

    id: row

    width: parent.width
    height: 16

    Text {
        //anchors.fill: parent
        text: modelData.content
        font.family: "Courier New"

        color: modelData.color
    }

    TextInput {
        //anchors.fill: parent
        //anchors.left: parent
        anchors.leftMargin: 20
        text: modelData.variable
        font.family: "Courier New"

        //color: modelData.color
    }


}
