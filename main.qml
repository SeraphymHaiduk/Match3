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
            enabled: !loader.sourceComponent
            onPressed: {
                gridModel.refillModel()
            }
        }

        Text{
            id:score
            anchors{
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: -parent.width/4
            }
            text: "score: " + gridModel.score
        }
        Text{
            id:steps
            anchors{
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: parent.width/4
            }
            text: "steps: " + gridModel.steps
        }
    }
    GameBoard{
        id:gameBoard
        model: gridModel
    }
    MyModel{
        id: gridModel
    }

    Connections{
        target: gridModel
        function onGameOver(){
            loader.sourceComponent = gameOverComponent
            loader.item.score = gridModel.score
            loader.item.steps = gridModel.steps
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
                gridModel.refillModel()
                loader.sourceComponent = undefined
            }
        }
    }
}
