import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Plugins.ModelPlugin 1.0
ApplicationWindow {
    id: root
    width:  640
    height: 480
    minimumWidth: 400
    minimumHeight: 400
    visible: true
    title: qsTr("Hello World")
    header: Rectangle{
        id:header
        width: root.width
        height: root.height*0.2
        color: "cyan"
        Button{
            id: restartBt
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
    }

    Connections{
        target: gameBoard.model
        function onGameOver(){
            loader.sourceComponent = gameOverComponent
            loader.item.score = gameBoard.model.score
            loader.item.steps = gameBoard.model.steps
            restartBt.enabled = false
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
                restartBt.enabled = true
            }
        }
    }
}
