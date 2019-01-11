import QtQuick 2.9
import QtQuick.Controls 2.2
import TimeLine 1.0

Item {

    id: root

    property int  groupIndex: 0
    property int  fromMs: 0
    property int  toMs: 0
    property int  duration: 0
    property int  infoGroupWidth: root.width/10
    signal changeFromAndToMoment(int from, int to)
    signal timeLineSelected(int groupIndex)
    signal timeSlotSelect(int timeSlotIndex)
    signal timeSlotAdded(int timeSlotIndex)
    signal timeSlotRemoved()
    signal updateAllTimeSlots()
    property int  currentCopyIndex: -1
    property bool  selected: false
    signal refreshPlease()

    //    onSelectedChanged: {
    //        timeLine.selected = selected
    //    }

    function collisionCheck(timeSlotId)
    {
        var theList = returnTimeSlotList()


    }
    Connections{
        target: theInterfaceGod
        onGui_timeSLotChanged:
        {
            root.refreshPlease()

        }
    }

    function returnTimeSlotList()
    {
        switch(root.groupIndex)
        {
        case 0:
            return timeSlotList_0

        case 1:
            return timeSlotList_1

        case 2:
            return timeSlotList_2

        case 3:
            return timeSlotList_3

        case 4:
            return timeSlotList_4

        case 5:
            return timeSlotList_5

        case 6:
            return timeSlotList_6

        case 7:
            return timeSlotList_7

        case 8:
            return timeSlotList_8

        }
    }


    Row
    {
        Rectangle{
            width: root.width / 10
            height: root.height
            color: "white"

            radius: 0
            Column{

                anchors.fill: parent
                Label{
                    text: "Kiểu " + (root.groupIndex + 1)
//                   anchors.horizontalCenter: parent.horizontalCenter
//                   anchors.verticalCenter: parent.verticalCenter
                    font.bold: true


                }
                Button{
                    text: "Update"
                    onClicked: {
                        var theList = root.returnTimeSlotList();
                        theList.updateAllTimeSlots()
                    }
                }
            }


        }
        Timeline{
            id: timeLine
            width: root.width/10 * 9
            height: root.height
            fromMs: root.fromMs
            toMs: root.toMs
            duration: root.duration
            selected: root.selected



            onChangeFromAndToMoment: {
                root.changeFromAndToMoment(from,to)
            }

            onTimeLineSelect: {
                root.timeLineSelected(root.groupIndex)
            }

            onNewTimeSlot: {
                var list = returnTimeSlotList()

                list.appendItem(root.groupIndex,from,to)

                root.timeSlotAdded(list.lastIndex())

            }

            onPaseTimeSlot: {
//                console.log("PASTE NEW TIMESLOT: " +from)

                var list = returnTimeSlotList()
                list.copyItem(root.currentCopyIndex, from)
            }



            Repeater{
                id: timeSlotRepeater



                model:TimeSlotModel{
                    id: dmModel
                    list: root.returnTimeSlotList()

                    onListChanged: {
//                        console.trace()
//                        console.log("List changed")
                        dmModel.list = root.returnTimeSlotList()

                    }
                }




                property int  timeSlotSelectedIndex: -1


                delegate: TimeLineSlot{
                    id: theTimeLineSlot
                    z: 2

                    property int  timeSlotIndex: theId

                    valveMode: ValveMode
                    height: timeLine.height
                    timeLineFromMs: root.fromMs
                    timeLineToMs: root.toMs
                    timeLineWidth:  timeLine.width
                    duration: root.duration
                    valveModeName: ValveModeName
                    valveSpeed: ValveSpeed
                    ledModeName: LedModeName
                    ledSpeed: LedSpeed
                    dmLedMode: LedModeHihi
                    ledColorList: LEDValuesList


                    Connections{
                        target: root

                        onRefreshPlease:
                        {

                            theTimeLineSlot.ledModeName = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex, "LedModeName")
                            theTimeLineSlot.valveSpeed = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex, "ValveSpeed")
                            theTimeLineSlot.ledSpeed = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex, "LedSpeed")
                            theTimeLineSlot.valveModeName = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex, "ValveModeName")
                            theTimeLineSlot.ledColorList = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex,"LEDValuesList")
                            theTimeLineSlot.timeSlotToMs = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex,"ToMs")
                            theTimeLineSlot.valveForceRepeat = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex,"ValveForceRepeat")
                            theTimeLineSlot.valveForceRepeatTimes = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex,"ValveForceRepeatTimes")
                            theTimeLineSlot.ledForceRepeat = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex,"LedForceRepeat")
                            theTimeLineSlot.ledForceRepeatTimes = dmModel.getDataPerIndex(theTimeLineSlot.timeSlotIndex,"LedForceRepeatTimes")


                        }
                    }

                    onDeleteTimeSlot: {

                        root.timeSlotRemoved()
                        var list = root.returnTimeSlotList()
                        list.removeItems(theId)
                    }

                    Component.onCompleted: {
                        timeSlotFromMs = FromMs
                        timeSlotToMs = ToMs
                    }

                    onTimeSlotFromMsChanged:
                    {
                        FromMs = timeSlotFromMs
                    }
                    onTimeSlotToMsChanged:
                    {
                        ToMs = timeSlotToMs
                    }

                    onTimeSlotSelect:
                    {
                        timeSlotRepeater.timeSlotSelectedIndex = theTimeLineSlot.timeSlotIndex
                        root.timeSlotSelect(theTimeLineSlot.timeSlotIndex)
                    }

                    onCopyTimeSlot:
                    {
                        root.currentCopyIndex = theId
                    }

                    timeSlotSelected:{

                        if(root.selected)
                        {
                            if(theTimeLineSlot.timeSlotIndex == timeSlotRepeater.timeSlotSelectedIndex)
                            {
                                true
                            }
                            else
                            {
                                false
                            }
                        }
                        else
                        {
                            false
                        }


                    }


                    onCheckCollision: {

                        //                        FromMs = theTimeLineSlot.timeSlotFromMs
                        //                        ToMs = theTimeLineSlot.timeLineToMs
                        var list = root.returnTimeSlotList()
                        var colliedOffset = list.timeSlotCollisionCheck(theId)

                        if(colliedOffset !== 0)
                        {
                            theTimeLineSlot.collided = true
                            theTimeLineSlot.rightCollision = list.getCollisionSide()

                            if(theTimeLineSlot.edgeSelected)
                            {
                                if(theTimeLineSlot.rightCollision)
                                {
                                    theTimeLineSlot.timeSlotToMs = FromMs + theTimeLineSlot.slotDuration
                                }
                                else
                                {
                                    theTimeLineSlot.timeSlotFromMs = colliedOffset
                                }

                            }
                            else
                            {
                                theTimeLineSlot.timeSlotFromMs = colliedOffset
                                theTimeLineSlot.timeSlotToMs = FromMs + theTimeLineSlot.slotDuration
                            }

                        }
                        else
                        {
                            theTimeLineSlot.collided = false
                        }
                    }

                }
            }
        }
    }
}
