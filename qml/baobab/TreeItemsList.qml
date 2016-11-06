import QtQuick 2.4

Column {
    Repeater {
        model:  modelData.childItems
        delegate: TreeItemView { }
    }
}
