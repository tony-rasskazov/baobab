import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Конфигурация объектов")
    width: 1024
    height: 520
    visible: true
    id: appWnd


    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }

    Action {
        id: newAction;
        text: qsTr("&New")
        iconSource: "qrc:/img/document-new.png"

        onTriggered: {
            //messageDialog.show(qsTr("New action triggered"));
        }
    }


    Action {
        id: openAction;
        text: qsTr("&Open")
        iconSource: "qrc:/img/document-open.png"

        onTriggered: {
            programmModel.open("persist.cfg");
            //messageDialog.show(qsTr("Open action triggered"));
        }
    }

    Action {
        id: saveAction;
        text: qsTr("&Save")
        iconSource: "qrc:/img/document-save.png"

        onTriggered: {
            programmModel.save("persist.cfg");
            //messageDialog.show(qsTr("Save action triggered"));
        }
    }

    Action {
        id: saveAsAction;
        text: qsTr("Save as...")
        iconSource: "qrc:/img/document-save-as.png"

        onTriggered: {
            //messageDialog.show(qsTr("Save as... action triggered"));
        }
    }

    Action {
        id: undoAction;
        text: qsTr("Undo")
        iconSource: "qrc:/img/edit-undo.png"

        onTriggered: {
            //messageDialog.show(qsTr("Undo action triggered"));
        }
    }

    Action {
        id: redoAction;
        text: qsTr("Undo")
        iconSource: "qrc:/img/edit-redo.png"

        onTriggered: {
            //messageDialog.show(qsTr("Redo action triggered"));
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem { action: newAction }
            MenuItem { action: openAction }
            MenuItem { action: saveAction }
            MenuItem { action: saveAsAction }
            MenuItem { action: undoAction }
            MenuItem { action: redoAction }
        }
        Menu {
            title: qsTr("&Developer")
            MenuItem {
                id: viewTreeLayoutMenu
                text: qsTr("View Tree Layout")
                checkable: true
                checked: false
            }
        }
    }

    toolBar: ToolBar {
        height: 38

        Row {
            anchors.fill: parent

            ToolButton { action: newAction }
            ToolButton { action: openAction }
            Item {
                height: 36
                width: 15
            }
            ToolButton { action: saveAction }
            ToolButton { action: saveAsAction }
            Item {
                height: 36
                width: 15
            }
            ToolButton { action: undoAction }
            ToolButton { action: redoAction }
        }
    }

    MainForm {
        id: form

        anchors.fill: parent

        hierarchyList.model: programmModel.tree
        hierarchyList.delegate: TreeItemView {}
        hierarchyList.highlightFollowsCurrentItem: true
        hierarchyList.highlight: Rectangle {
            border.color: "lightgray"
            color: "#f5f5f5"
            radius: 2
        }


        mindListView.model: programmModel.tree
        mindListView.delegate: TreeItemView {}
        mindListView.highlightFollowsCurrentItem: true
/*
        mindView.model: programmModel.tree
        mindView.delegate: TreeItemView {}
        mindView.highlightFollowsCurrentItem: true
*/
        addPlantBtn.onClicked: {
            console.log("Insert top level item");
            var x;
            var c = programmModel.insertChild(x);
            programmModel.tree.push(c);
            c.selected = true;
        }
    }
}
