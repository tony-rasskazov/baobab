import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    id: rootItem
    width: 1000
    height: 600
    antialiasing: false
    smooth: false

    property alias hierarchyList: hierarchyList

    property alias viewDetailsBtn: viewDetailsBtn

    property alias mindView: mindView
    property alias mindListView: mindListView

    property alias detailRect: detailRect

    property alias addPlantBtn: addPlantBtn

    SplitView {
        id: splitView
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        orientation: Qt.Horizontal

        Rectangle {
            id: listRect
            x: 0
            y: 29
            width: 535
            color: "#ffffff"
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            z: -3

            ListView {
                id: hierarchyList
                anchors.topMargin: 26
                anchors.fill: parent
                delegate: TreeItemView {}
            }

            ScrollBar {
                flickable: hierarchyList;
            }

            Rectangle {
                id: buttonsBarRect
                height: 24
                color: "#e7e7e7"
                radius: 1
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                border.color: "#d3d3d3"
                anchors.left: parent.left
                anchors.leftMargin: 0

                Button {
                    id: addPlantBtn
                    x: 2
                    y: 2
                    width: 20
                    height: 20
                    text: qsTr("")

                    tooltip: qsTr("Добавить объект")
                    activeFocusOnPress: false
                    iconSource: "qrc:/img/table-cell-insert.ico"

                }

                Button {
                    id: viewDetailsBtn
                    x: 512
                    y: 2
                    width: 20
                    height: 20
                    text: qsTr("")
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    checkable: true
                    checked: true
                    tooltip: qsTr("Детализация")
                    iconSource: "qrc:/img/more.png"
                }

                Rectangle {
                    id: filterRect
                    x: 28
                    y: 3
                    height: 18
                    color: "#ffffff"
                    radius: 2
                    border.color: "#7e7e7e"
                    anchors.left: parent.left
                    anchors.leftMargin: 28
                    anchors.right: parent.right
                    anchors.rightMargin: 271

                    TextInput {
                        id: filterInput
                        color: "#a3a3a3"
                        text: qsTr("Фильтр")
                        anchors.fill: parent
                        font.pixelSize: 12
                    }
                }

                Button {
                    id: applyFilterBtn
                    x: 270
                    y: 2
                    width: 20
                    height: 20
                    text: qsTr("")
                    anchors.right: parent.right
                    anchors.rightMargin: 245
                    activeFocusOnPress: false
                    iconSource: "qrc:/img/apply.png"
                    tooltip: qsTr("Добавить объект")
                }
            }

        }

        Rectangle {
            id: detailRect
            x: 536
            y: 0
            width: 240
            height: 520
            color: "#ffffff"
            anchors.right: parent.right
            anchors.rightMargin: 0
            border.color: "#d3d3d3"


            Item {
                id: detailBarRect
                height: 24
                anchors.top: parent.top
                anchors.topMargin: 0
                //color: "#e7e7e7"
                //b/order.color: "lightgray"
                //radius: 1
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                Row {
                    id: row1
                    spacing: 3
                    anchors.fill: parent

                    Button {
                        id: viewDataBtn
                        text: qsTr("Данные")
                        enabled: false
                        activeFocusOnPress: true
                        isDefault: false
                        checked: true
                        checkable: true
                    }

                    Button {
                        id: viewParamsBtn
                        text: qsTr("Параметры")
                        enabled: false
                    }

                    Button {
                        id: viewOtherBtn
                        text: qsTr("Дополнительно")
                        enabled: false
                    }
                }
            }

            GridView {
                id: mindView
                x: -20
                y: 461
                width: 257
                height: 203
                delegate: Item {
                    x: 5
                    height: 50
                    Column {
                        Rectangle {
                            width: 40
                            height: 40
                            color: colorCode
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Text {
                            x: 5
                            text: name
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.bold: true
                        }
                        spacing: 5
                    }
                }
                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                    }

                    ListElement {
                        name: "Green"
                        colorCode: "green"
                    }
                }
                cellHeight: 70
                cellWidth: 70
            }

            ListView {
                id: mindListView
                anchors.topMargin: 26
                anchors.fill: parent
                delegate: Item {
                    x: 5
                    width: 80
                    height: 40
                    Row {
                        id: row2
                        Rectangle {
                            width: 40
                            height: 40
                            color: colorCode
                        }

                        Text {
                            text: name
                            anchors.verticalCenter: parent.verticalCenter
                            font.bold: true
                        }
                        spacing: 10
                    }
                }
                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                    }

                    ListElement {
                        name: "Green"
                        colorCode: "green"
                    }
                }
            }



        }

    }

    states: [
        State {
            name: "NoDetails"

            PropertyChanges {
                target: detailRect
                visible: false
                width: 0
            }

            PropertyChanges {
                target: rootItem
                width: 535
            }
        }
    ]
}
