import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import CppModel 1.0
ApplicationWindow {
    id: root
    width:  640
    height: 480
    visible: true
    title: qsTr("Hello World")
    header: Rectangle{
        id:header
        width: root.width
        height: root.height*0.2
        color: "red"
    }
    GameBoard{
        id:gameBoard
        anchors{
            centerIn:parent
        }
        cellWidth: parent.width/model.columnsCount < parent.height/model.rowsCount ? parent.width/model.columnsCount : parent.height/model.rowsCount
        cellHeight: cellWidth
        height: parent.width/model.columnsCount > parent.height/model.rowsCount? parent.height : cellHeight*model.rowsCount
        width: parent.width/model.columnsCount < parent.height/model.rowsCount ? parent.width : cellWidth*model.columnsCount
    }
}
