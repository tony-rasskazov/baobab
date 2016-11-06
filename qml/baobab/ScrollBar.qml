import QtQuick 2.4

Item {
    id: scrollbar;
    width: (handleSize + 2 * (backScrollbar.border.width +1));
    visible: (flickable.visibleArea.heightRatio < 1.0);

    anchors {
        top: flickable.top;
        right: flickable.right;
        bottom: flickable.bottom;
        margins: 1;
    }

    property Flickable flickable               : null;
    property int       handleSize              : 10;

    function scrollDown () {
        flickable.contentY = Math.min (flickable.contentY + (flickable.height / 4), flickable.contentHeight - flickable.height);
    }

    function scrollUp () {
        flickable.contentY = Math.max (flickable.contentY - (flickable.height / 4), 0);
    }

    Binding {
        target: handle;
        property: "y";
        value: (flickable.contentY * clicker.drag.maximumY / (flickable.contentHeight - flickable.height));
        when: (!clicker.drag.active);
    }

    Binding {
        target: flickable;
        property: "contentY";
        value: (handle.y * (flickable.contentHeight - flickable.height) / clicker.drag.maximumY);
        when: (clicker.drag.active || clicker.pressed);
    }

    Rectangle {
        id: backScrollbar;
        radius: 2;
        antialiasing: true;
        color: Qt.rgba(1.0, 1.0, 1.0, 0.85);
        anchors { fill: parent; }

        border {
            width: 1;
            color: "lightgray";
        }

        MouseArea {
            anchors.fill: parent;
            onClicked: { }
        }
    }

    MouseArea {
        id: btnUp;
        height: width;

        anchors {
            top: parent.top;
            left: parent.left;
            right: parent.right;
            margins: (backScrollbar.border.width +1);
        }

        onClicked: { scrollUp (); }

        Rectangle {
            color: (btnUp.pressed ? "darkgray" : "#00000000");
            anchors.fill: parent;
            radius: 2
        }

        Image {
            anchors.fill: parent
            source: "qrc:/img/scrollbar_top_arrow.png"
        }
    }

    MouseArea {
        id: btnDown;
        height: width;
        anchors {
            left: parent.left;
            right: parent.right;
            bottom: parent.bottom;
            margins: (backScrollbar.border.width +1);
        }
        onClicked: { scrollDown (); }

        Rectangle {
            color: (btnDown.pressed ? "darkgray" : "#00000000");
            anchors.fill: parent;
            radius: 2
        }

        Image {
            anchors.fill: parent
            source: "qrc:/img/scrollbar_bottom_arrow.png"
        }
    }

    Item {
        id: groove;
        clip: true;
        anchors {
            fill: parent;
            topMargin: (backScrollbar.border.width +1 + btnUp.height +1);
            leftMargin: (backScrollbar.border.width +1);
            rightMargin: (backScrollbar.border.width +1);
            bottomMargin: (backScrollbar.border.width +1 + btnDown.height +1);
        }

        MouseArea {
            id: clicker;
            drag {
                target: handle;
                minimumY: 0;
                maximumY: (groove.height - handle.height);
                axis: Drag.YAxis;
            }
            anchors { fill: parent; }
            onClicked: { flickable.contentY = (mouse.y / groove.height * (flickable.contentHeight - flickable.height)); }
        }

        Item {
            id: handle;
            height: Math.max (20, (flickable.visibleArea.heightRatio * groove.height));
            anchors {
                left: parent.left;
                right: parent.right;
            }

            Rectangle {
                id: backHandle;
                color: (clicker.pressed ? "black" : "darkgray");
                opacity: (flickable.moving ? 0.65 : 0.40);
                anchors { fill: parent; }
                radius: 2

                Behavior on opacity { NumberAnimation { duration: 100; } }
            }
        }
    }
}
