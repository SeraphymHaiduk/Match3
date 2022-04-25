import QtQuick 2.0
import QtQuick.Controls 2.15
import CppModel 1.0

GridView{
    id: root
    visible: true
    model: MyModel{
        id:gridModel
    }
    Component.onCompleted: console.log(root.width)
    interactive: false
    move:Transition{
        NumberAnimation{
            properties: "x,y"
            duration:400
        }
    }
    displaced : Transition {
        NumberAnimation{
            properties: "x,y"
            duration: 400
        }
    }
    Connections{
        target: root.model
        function onRightChoise(firstChoise, secondChoise, matchesToRemove){
            model.setState(firstChoise,"nonSqueezed")
            model.setState(secondChoise,"nonSqueezed")
            console.log(matchesToRemove)
            for(var a = 0; a < matchesToRemove.length;a++){
                for(var i= 0; i< matchesToRemove[a].length; i++){
                    console.log(matchesToRemove[a][i])
                    model.setState(matchesToRemove[a][i],"deleted")
                }
            }

        }
        function onWrongChoise(firstChoise, secondChoise){
            model.setState(firstChoise,"wrong")
            model.setState(secondChoise,"wrong")
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
            state: model.state
            states: [
                State{
                    name: "nonSqueezed"
                    PropertyChanges {
                        target: circle
                        anchors.margins: tile.width*0.05
                        opacity:1
                    }
                },
                State{
                    name: "squeezed"
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
                Transition {
                    id: squeezTransition
                    to: "squeezed"
                    NumberAnimation{
                        properties: "anchors.margins"
                        duration:200
                        easing.type: Easing.OutCirc
                    }
                    onRunningChanged: {
                        if(running === false){
                            root.model.pressOn(index)
                        }
                    }
                },
                Transition {
                    to: "nonSqueezed"
                    NumberAnimation{
                        properties: "anchors.margins"
                        duration: 200
                        easing.type: Easing.InCirc
                    }
                },
                Transition {
                    to: "wrong"
                    NumberAnimation {
                        properties: "anchors.margins"
                        duration: 600
                        easing.type: Easing.OutElastic
                    }
                },
                Transition{
                    to: "deleted"
                    NumberAnimation{
                        properties: "anchors.margins,opacity"
                        duration: 400

                    }
                    onRunningChanged: {
                        if(running === false){
                            console.log("removeMatch")
                            root.model.removeMatches()
                        }
                    }
                }

            ]
            Label{
               anchors.centerIn: parent
               text: index + colorName
            }
            MouseArea{
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: false
                onPressed: {
                    if(model.state === "squeezed"){
                        model.state = "nonSqueezed"
                    }
                    else{
                        model.state = "squeezed"
                    }
                }
            }
        }
    }
}
