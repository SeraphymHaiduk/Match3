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
        color: "cyan"
        Button{
            height: parent.height*0.6
            width: parent.width/4
            anchors.centerIn: parent
            text: "restart"
            onPressed: {
                gameBoard.model.populate()
            }
        }

        Text{
            id:score
            anchors{
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: -parent.width/4
            }
            text: "score: "+gameBoard.model.score
        }
        Text{
            id:steps
            anchors{
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: parent.width/4
            }
            text: "steps: "+gameBoard.model.steps
        }
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

    Connections{
        target: gameBoard.model
        function onGameOver(){
            loader.sourceComponent = gameOverComponent
            loader.item.score = gameBoard.model.score
            loader.item.steps = gameBoard.model.steps
        }
    }

    Loader{
        id: loader
        anchors.fill: parent
        sourceComponent: undefined
    }

    Component{
        id: gameOverComponent
        GameOverMenu{
            anchors.fill: parent
            onNewGame: {
                gameBoard.model.populate()
                loader.sourceComponent = undefined
            }
        }
    }
}
