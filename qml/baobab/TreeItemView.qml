import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Dialogs 1.2

Row {

    id: row
    //width: 200

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"

        //property alias item: item
        //modality: Qt.WindowModal
        //parent: form
        onAccepted: {
            console.log("You chose: " + colorDialog.color);
//            modelData.color = colorDialog.color;
        }

        onRejected: {
            console.log("Canceled")
        }

        Component.onCompleted: {

            visible = false;
            //color = "red";
        }
        showAlphaChannel: false
        color: "white"
        //Qt бага!!! тут валится в MacOS-> color: programmModel.selectedItem.color
        //visible: false
    }

    Rectangle {
        width: 20
        height: 20
        color: modelData.highlighted  ? "#afafaf" : "#00000000"

        radius: 0

        Image {
            id: iconImg
            //id: iconImg

            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2
            source: !modelData.hasChild ? "qrc:/img/code-variable.png" : modelData.isOpen ? modelData.imageOpenUrl : modelData.imageUrl
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                modelData.isOpen = !modelData.isOpen;
            }
        }
    }

    Column {
        id: col

        //!  переделать Rectangle на Row
        Rectangle {
            id: rect
            height: 20
            width: 200

//            border.color : modelData.subSelected ? "darkgray" : "#00000000"
//            color: viewTreeLayoutMenu.checked  ? "#44ff0000" : modelData.subSelected ? "lightgray" : "#00000000"
            border.color : "#00000000"
            color: viewTreeLayoutMenu.checked  ? "#44ff0000" : "#00000000"
            radius: 2

            TextInput {
                id: content
                height: 20
                enabled: modelData.selected

                text: modelData.content
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: modelData.color
                font.family: "Courier New"
                wrapMode: TextEdit.NoWrap

                onTextChanged: {
                    modelData.content = text;
                }
            }

            Rectangle {
                //x: - (modelData.level + 1) * 20
                x: 0
                //y: col.top
                width: col.width
                height: 20
                color: viewTreeLayoutMenu.checked  ? "#3300ff00" : modelData.highlighted  ? "#afafaf" : "#00000000"
                z:-1


                //MouseArea перед иконкой элемента
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    /*
                    propagateComposedEvents: true
                    onPressed: mouse.accepted = false;
                    onReleased: mouse.accepted = false;
                    onDoubleClicked: mouse.accepted = false;
                    onPositionChanged: mouse.accepted = false;
                    onPressAndHold: mouse.accepted = false;
                    */
                    onEntered: {
                        modelData.highlighted = true;
                    }

                    onClicked: {
                    //mouse.accepted = false;
                        modelData.selected = true;
                    }

                    onDoubleClicked: {
                        modelData.isOpen = !modelData.isOpen;
                    }

                }
            }


            Rectangle {
                x: - (modelData.level + 1) * 20
                y: 0
                width: (modelData.level) * 20
                height: 20
                color: viewTreeLayoutMenu.checked  ? "#3300ff00" : modelData.highlighted  ? "#afafaf" : "#00000000"
                z:-100

                //MouseArea после иконки элемента
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        modelData.highlighted = true;
                    }
                    onClicked: {
                        modelData.selected = true;
                    }
                    onDoubleClicked: {
                        modelData.isOpen = !modelData.isOpen;
                    }
                }
            }

            Rectangle {
                anchors.fill: content
                border.color: modelData.selected ? "black" : modelData.subSelected ? "darkgray" : "#00000000"
                color: modelData.selected ? "darkgray" : modelData.subSelected ? "lightgray" : "#00000000"
                radius: 2
                z: -1
            }


            Button {
                width: 16
                height: 16
                anchors.left: parent.left
                anchors.leftMargin: content.width + 7
                anchors.top: parent.top
                anchors.topMargin: 2
                iconSource: "qrc:/img/table-cell-insert.ico"
                visible: modelData.subSelected | modelData.selected
                opacity: 0.67
                onClicked: {
                    //console.log("Insert child");
                    var c = programmModel.insertChild(modelData);
                    c.selected = true;
                }
            }

            Button {
                width: 16
                height: 16
                anchors.left: parent.left
                anchors.leftMargin: content.width + 29
                anchors.top: parent.top
                anchors.topMargin: 2

                iconSource: "qrc:/img/delete_icon.png"
                visible: modelData.selected
                opacity: 0.67
                onClicked: {
                    console.log("Delete child");
                    programmModel.deleteChild(modelData);
                }
            }
        }


        Loader {
            source: modelData.isOpen ? "qrc:/qml/baobab/TreeItemsList.qml" : "qrc:/qml/baobab/Empty.qml"
        }
    }
}
