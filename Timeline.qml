import QtQuick 2.9
import QtQuick.Controls 2.2
Item {

    id: root
    property int  timeLineWidth: 640
    property int  timelineHeight: 80
    property int  fromMs: 0
    property int toMs: 60000
    property int  duration: 240000
    signal changeFromAndToMoment(int from, int to)
    signal newTimeSlot(int from, int to)
    signal paseTimeSlot(int from)
    signal timeLineSelect()
    property bool selected: false

    onSelectedChanged: {
        if(!root.selected)
        {
            selectRec.visible = false
        }
    }

    Rectangle
    {
        id: timelineBG
        width: root.width
        height: root.height
        color: "grey"

        MouseArea
        {
            id: timeLineMainMouseArea
            anchors.fill: parent
            property int  initialX: 0
            acceptedButtons: Qt.RightButton | Qt.LeftButton

            function zoomTimeLine(angleDelta)
            {
                var theMsZoomStep = 0
                var theCurrentDuration = Math.abs(root.toMs - root.fromMs)
                if( theCurrentDuration<= 1000)
                {
                    theMsZoomStep = 50
                }
                else if(theCurrentDuration <= 60000)
                {
                    theMsZoomStep = 1000
                }
                else
                {
                    theMsZoomStep = 5000
                }

                if(angleDelta > 0)
                {


                    if(root.toMs >= root.duration)
                    {
                        //                        root.fromMs = 0
                        //                        root.toMs = root.duration

                        root.changeFromAndToMoment(0, root.duration)

                    }

                    else if(root.toMs < root.duration)
                    {
                        //                        root.toMs = root.toMs + theMsZoomStep
                        root.changeFromAndToMoment(root.fromMs, root.toMs + theMsZoomStep)

                    }
                    else
                    {
                        root.changeFromAndToMoment(root.fromMs, root.duration)
                        //                        root.toMs = root.duration

                    }

                }
                else
                {

                    if(Math.abs(root.toMs - root.fromMs) > 500)
                    {
                        //                        root.toMs = root.toMs - theMsZoomStep
                        root.changeFromAndToMoment(root.fromMs, root.toMs - theMsZoomStep)
                    }
                }

            }

            onPressed: {

                if(pressedButtons & Qt.LeftButton)
                {

                    root.timeLineSelect()
                    selectRec.width = 1
                    selectRec.height = root.height
                    selectRec.visible = true
                    selectRec.x = timeLineMainMouseArea.mouseX
                    selectRec.y = timeLineMainMouseArea.mouseY
                    timeLineMainMouseArea.initialX = mouseX
                }
                if(pressedButtons & Qt.RightButton && root.selected)
                {
                    componentContextMenu.x = mouseX
                    componentContextMenu.open()

                }

            }

            onReleased: {
                if (selectRec.width ==1)
                {
                    selectRec.width = 0
                    selectRec.visible = false
                }

            }

            Menu
            {
                id: componentContextMenu

                MenuItem{
                    id: componentDeleteMenuItem
                    text: qsTr("New")

                    onClicked: {
                        var selectedFromMs = (selectRec.x / timelineBG.width * Math.abs(root.toMs - root.fromMs) ) + root.fromMs
                        var selectedToMs = ((selectRec.width + selectRec.x )/ timelineBG.width * Math.abs(root.toMs - root.fromMs) ) + root.fromMs

                        if(selectedToMs - selectedFromMs <50)
                        {
                            return
                        }

                        root.newTimeSlot(selectedFromMs,selectedToMs)
                    }

                }

                MenuItem{
                    id: pasteMenuItem
                    text: qsTr("Paste")

                    onClicked: {
                        root.paseTimeSlot((timeLineMainMouseArea.mouseX / timelineBG.width * Math.abs(root.toMs - root.fromMs) ) + root.fromMs)
                    }
                }


            }

            onMouseXChanged: {

                if(pressedButtons & Qt.LeftButton)
                {
                    if(mouseX > selectRec.x && selectRec.x >= 0) // ben phai
                    {
                        selectRec.width = mouseX - selectRec.x
                    }
                    else if(mouseX < selectRec.x && selectRec.x > 0)
                    {
                        selectRec.x = mouseX
                        selectRec.width = Math.abs(mouseX - timeLineMainMouseArea.initialX)
                    }
                    if((selectRec.x + selectRec.width) >= root.width)
                    {
                        selectRec.width = root.width - selectRec.x

                    }
                    if(selectRec.x <= 0)
                    {
                        selectRec.x = 0
                    }
                }




            }

            onClicked: {

            }

            onWheel: {
                timeLineMainMouseArea.zoomTimeLine(wheel.angleDelta.y)

            }

        }

        Rectangle{
            id: selectRec
            width: 0
            height: 0
            anchors.top: parent.top
            visible: false
            color: "black"
            opacity: 0.5
            border.color: "black"
            border.width: 1
        }
    }


}
