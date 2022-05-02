import QtQuick 2.0
import QtQml 2.15
import QtQuick.Controls 2.15
import Plugins.ModelPlugin 1.0

GridView{
    id: root
    visible: true
    model: MyModel{
        id:gridModel
    }
    Component.onCompleted: console.log(root.width)
    interactive: false
    property int moveDuration: 400
    property int pressDuration: 200
    property int unpressDuration: pressDuration
    property int unpressWrongDuration: pressDuration*3
    property int deleteDuration: pressDuration*2
    add:Transition{
        NumberAnimation{
            properties: "y"
            from: -cellHeight-(root.height-to)
            duration: root.moveDuration
        }
    }
    move:Transition{
        id: moveTransition
        NumberAnimation{
            properties: "x,y"
            duration: root.moveDuration
        }
    }
    displaced : Transition {
        NumberAnimation{
            properties: "x,y"
            duration: root.moveDuration
        }
    }
    Timer{
        id: animationTimer
        repeat: false
        property var functionToExec
        function exec(duration, foo){
            animationTimer.functionToExec = foo
            animationTimer.interval = duration
            animationTimer.start()
        }
        onTriggered: {
            functionToExec()
        }
    }

    Connections{
        target: root.model
        function onMatchesHappened(){
            animationTimer.exec(root.moveDuration>root.unpressDuration? root.moveDuration : root.unpressDuration,function(){
                root.model.readyToDisappear()
                animationTimer.exec(root.deleteDuration,function(){
                    root.model.readyToRemove()
                })
            })
        }
    }

    delegate: Item{
        id: tile
        width: cellWidth
        height: cellHeight
        visible: true

        Rectangle{
            id: circle
            anchors.fill: parent
            radius: width/2
            color: colorName
            visible: true
            clip:true
            anchors.margins: tile.width*0.05
            state: root.model.stateToString(model.state)
            states: [
                State{
                    name: "unpressed"
                    PropertyChanges {
                        target: circle
                        anchors.margins: tile.width*0.05
                        opacity:1
                    }
                },
                State{
                    name: "pressed"
                    PropertyChanges{
                        target: circle
                        anchors.margins: tile.width*0.15
                        opacity: 1
                    }
                },
                State{
                    name: "wrong"
                    PropertyChanges{
                        target:circle
                        anchors.margins: tile.width*0.05
                        opacity:1
                    }
                },
                State{
                    name: "deleted"
                    PropertyChanges {
                        target: circle
                        opacity: 0
                        anchors.margins: -tile.width*0.05
                    }
                }

            ]
            transitions: [
                Transition {        //press
                    to: "pressed"
                    NumberAnimation{
                        properties: "anchors.margins"
                        duration: root.pressDuration
                        easing.type: Easing.OutCirc
                    }
                },
                Transition {        //unpress
                    to: "notpressed"
                    NumberAnimation{
                        properties: "anchors.margins"
                        duration: root.unpressDuration
                        easing.type: Easing.InCirc
                    }
                },
                Transition {        //wrong
                    to: "wrong"
                    NumberAnimation {
                        properties: "anchors.margins"
                        duration: root.unpressWrongDuration
                        easing.type: Easing.OutElastic
                    }
                },
                Transition{         //delete
                    to: "deleted"
                    NumberAnimation{
                        properties: "anchors.margins,opacity"
                        duration: root.deleteDuration
                    }
                }

            ]
//            Label{
//               anchors.centerIn: parent
//               text: index + colorName + "\n" + model.state
//            }
            MouseArea{
                id: mouseArea
                anchors.fill: parent
                enabled: model.state === MyModel.ElementState.Deleted || moveTransition.running ? false : true
                hoverEnabled: false
                onPressed: root.model.pressOn(index)
            }
        }
    }
}
