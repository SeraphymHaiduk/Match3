import QtQuick 2.0
import QtQml 2.15
import QtQuick.Controls 2.15
import Plugins.ModelPlugin 1.0

GridView{
    id: root
    anchors.centerIn: parent
    height: parent.width/model.columnsCount > parent.height/model.rowsCount? parent.height : cellHeight*model.rowsCount
    width: parent.width/model.columnsCount < parent.height/model.rowsCount ? parent.width : cellWidth*model.columnsCount
    cellWidth: parent.width/model.columnsCount < parent.height/model.rowsCount ? parent.width/model.columnsCount : parent.height/model.rowsCount
    cellHeight: cellWidth

    property int moveDuration: 400
    property int pressDuration: 200
    property int unpressDuration: pressDuration
    property int unpressWrongDuration: pressDuration*5
    property int deleteDuration: pressDuration*2

    property int draggedItemIndex: -1
    property int draggedItemX
    property int draggedItemY

    property int circleW: cellWidth*0.9
    property int circleH: cellHeight*0.9

    property int horizontalOffset: 0
    property int verticalOffset: 0

    property bool moveTransitionEnabled: true
    signal offset(int x, int y, int offsetIndex)

    Item{
        id:dndContainer
    }
    visible: true
    Connections{
        target: root.model
        function onMatchesHappened(){
            moveTransitionEnabled = true
            mouseHandler.enabled = false
            animationTimer.exec(root.moveDuration,function(){
                root.model.readyToDisappear()
                animationTimer.exec(root.deleteDuration,function(){
                    root.model.readyToRemove()
                })
            })
        }
        function onMatchesNotHappened(){
            mouseHandler.enabled = true
        }
    }
    model: MyModel{
        id:gridModel
    }
    interactive: false


    add:Transition{
        NumberAnimation{
            properties: "y"
            from: -cellHeight-(root.height-to)
            duration: root.moveDuration
        }
    }
    move:Transition{
        id: moveTransition
        enabled: root.moveTransitionEnabled
        NumberAnimation{
            properties: "x,y"
            duration:  root.moveDuration
        }
    }
    displaced : Transition {
        enabled: root.moveTransitionEnabled
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



    delegate: Item{
        id: tile
        width: cellWidth
        height: cellHeight
        visible: true
        Connections{
            target: root
            function onOffset(x,y,offsetIndex){
                if(index === offsetIndex){
                    if(x !== 0){
                        circle.anchors.horizontalCenterOffset = -x
                    }
                    else if(y !== 0){
                        circle.anchors.verticalCenterOffset = -y
                    }

                }
                else{
                    circle.anchors.horizontalCenterOffset = 0
                    circle.anchors.verticalCenterOffset = 0
                }
            }
        }

        Rectangle{
            id: circle
            width: circleW
            height: circleH
            anchors.centerIn: tile

            radius: width/2
            color: colorName
            visible: true
            clip:true


            state: root.model.stateToString(model.state)
            states: [
//                State{
//                    name: "notpressed"
//                    PropertyChanges {
//                        target: circle
//                        anchors.margins: tile.width*0.05
//                        opacity:1
//                    }
//                },
                State{
                    name: "pressed"
                    PropertyChanges {
                        target: circle
                        parent: dndContainer
                        x: root.draggedItemX
                        y: root.draggedItemY
                        anchors.centerIn: undefined
                    }
                    PropertyChanges {
                        target: root
                        draggedItemX: mouseHandler.mouseX
                        draggedItemY: mouseHandler.mouseY
                    }
                },
                State{
                    name: "wrong"
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

                },
                Transition {        //wrong
                    to: "wrong"
                    SequentialAnimation{
                        NumberAnimation{
                            property: "scale"
                            duration: root.unpressWrongDuration/4*1
                            easing.type: Easing.InSine
                            to: 0.8
                        }
                        NumberAnimation {
                            properties: "scale"
                            to: 1
                            duration: root.unpressWrongDuration/4*3
                            easing.type: Easing.OutElastic
                        }
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

        }
    }

    MouseArea{
        id: mouseHandler
        anchors.fill: parent
        onReleased: {
            if(root.draggedItemIndex !== -1){
                root.model.pressOn(root.indexAt(mouseX,mouseY))
                root.draggedItemIndex = -1
            }
            root.offset(0,0,-1)
            root.moveTransitionEnabled = false
        }

        onPositionChanged: {
            if(root.draggedItemIndex !== -1){
                var j = root.draggedItemIndex%root.model.columnsCount
                var i = Math.trunc(root.draggedItemIndex/root.model.rowsCount)

                var normalX = cellWidth * j + cellWidth/2
                var normalY = cellHeight * i + cellHeight/2

                if(!(mouseX > (j+2) * cellWidth - cellWidth/2 ||
                    mouseX > cellWidth * root.model.columnsCount ||
                    mouseX < (j-1) * cellWidth + cellWidth/2)){

                    root.draggedItemX = mouseX - circleW/2
                    root.horizontalOffset = mouseX - normalX
                }

                if(!(mouseY < (i-1) * cellHeight + cellHeight/2 ||
                    mouseY > (i+2) * cellHeight - cellHeight/2 ||
                    mouseY > cellHeight * root.model.rowsCount)){

                    root.draggedItemY = mouseY - circleH/2
                    root.verticalOffset = mouseY - normalY
                }
                var indx
                var offset
                if(Math.abs(root.verticalOffset) > Math.abs(horizontalOffset)){
                    offset = root.verticalOffset
                    if(root.verticalOffset > 0){
                        indx = root.draggedItemIndex + root.model.columnsCount
                    }
                    else{
                        indx =  root.draggedItemIndex - root.model.columnsCount
                    }
                    if(indx >= 0 && indx < root.model.columnsCount*root.model.rowsCount){
                        root.offset(0,offset,indx)
                        console.log("vertical:", offset)
                    }
                }
                else{
                    offset = root.horizontalOffset
                    if(root.horizontalOffset > 0){
                        indx = root.draggedItemIndex + 1
                    }
                    else{
                        indx = root.draggedItemIndex - 1
                    }
                    if(indx >= 0 && indx < root.model.columnsCount*root.model.rowsCount){
                        root.offset(offset,0,indx)
                        console.log("horizontal:",offset)
                    }
                }
            }
        }

        onPressed: {
//            draggedItemX = mouseHandler.mouseX - circleW/2
//            draggedItemY = mouseHandler.mouseY - circleH/2
            root.draggedItemIndex = root.indexAt(mouseX,mouseY)
            root.model.pressOn(root.draggedItemIndex)
        }


    }
}
