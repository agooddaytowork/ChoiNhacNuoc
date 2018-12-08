import QtQuick 2.9
import QtQuick.Controls 2.2
import TimeLine 1.0
import Qt.labs.folderlistmodel 2.2
import QtQuick.Dialogs 1.2


Item {

    id:root

    property int  currentTimeSlotIndex: 0
    property int  currentGroupIndex: 0
    property int  currentValveModeIndex: 0
    property int  currentValveSpeed: 0
    property int  currentLedSpeed: 0
    property int  currentLedMode: 0
    property TimeSlotModel theTimeSlotModel: TimeSlotModel{list:returnTimeSlotList() }
    property bool groupIndexJustChanged: false
    property string currentLedColorList: "grey;grey"

    signal modelRefreshed()

    enabled: false




    function returnColor(index)
    {

        var colorArray = root.currentLedColorList.split(";")
        if(colorArray.length <= index)
        {
            return "#8e8e8e"
        }
        return colorArray[index]
    }




    function returnDurationString(duration)
    {
        var minutes="00"
        var seconds="00"
        var miliSeconds ="000"

        if(duration <=999)
        {
            miliSeconds = ("00" + duration).slice(-3)
            return "00m:00s:"+miliSeconds +"ms"
        }
        else if(duration <=59999)
        {
            seconds = ("0" + parseInt(duration/1000)).slice(-2)
            miliSeconds = ("00" + duration).slice(-3)

            return "00m:"+seconds+"s:"+miliSeconds+"ms"
        }
        else
        {
            minutes = ("0" + parseInt(duration/60000)).slice(-2)

            duration = duration%60000
            seconds = ("0" + parseInt(duration/1000)).slice(-2)
            miliSeconds =("00" + duration%1000).slice(-3)

            return minutes + "m:" + seconds + "s:" + miliSeconds+"ms"

        }
    }



    function updateValveData()
    {
        console.trace()
        console.log("Group: " + root.currentGroupIndex + " - timeslot: " + root.currentTimeSlotIndex
                    + " - valveMode: " + valveModeComboBox.currentIndex)
        //        if(theTimeSlotModel.size !== 0  && root.currentTimeSlotIndex <= theTimeSlotModel.size)
        //        {
        //        console.trace()



        if(valveForceRepeatCheckBox.checked)
        {
            switch(root.currentGroupIndex)
            {
            case 0:
            case 3:
            case 1:
            case 7:
            case 6:
            case 8:
            case 4:
                var currentFromMs = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"FromMs")
                var newToMs = valveEffectFolderModel.get(valveModeComboBox.currentIndex,"fileSize") * valveForceRepeatSpinbox.value * 50 *(51- speedValveSpinBox.value) +currentFromMs

                break
            case 2:
            case 5:
                currentFromMs = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"FromMs")
                newToMs = valveEffectFolderModel.get(valveModeComboBox.currentIndex,"fileSize")/2 * valveForceRepeatSpinbox.value * 50 *(51- speedValveSpinBox.value) +currentFromMs

                break


            }

            if(newToMs > theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"ToMs"))
            {
                messageDialog.title = "Valve - Forced Repeat Error"
                messageDialog.text = "Timeslot out of range! \n Please extend time slot until"+ root.returnDurationString(newToMs)+" \n or change valve speed, repeat time"
                messageDialog.icon = MessageDialog.Warning
                messageDialog.open()

                return
            }

        }


        theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"ValveForceRepeat",valveForceRepeatCheckBox.checked)
        theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"ValveForceRepeatTimes",valveForceRepeatSpinbox.value)
        theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"ValveMode", valveModeComboBox.currentIndex)
        theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"FileBinPath", valveEffectFolderModel.get(valveModeComboBox.currentIndex,"filePath"))
        theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"ValveSpeed",speedValveSpinBox.value)
        theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"ValveModeName", valveEffectFolderModel.get(valveModeComboBox.currentIndex,"fileName"))

        console.log(valveEffectFolderModel.get(valveModeComboBox.currentIndex,"fileSize"))
        if(valveForceRepeatCheckBox.checked)
        {
            theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"ToMs", newToMs)
        }

    }

    function updateValveEffectFolder()
    {
        switch(root.currentGroupIndex)
        {
        case 0:
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu1")
            break

        case 1:
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu2")
            break

        case 2:
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu3")
            break

        case 3:
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu4")
            break

        case 4:
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu5")
            break

        case 5:
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu6")
            break

        case 6:
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu7")
            break

        case 7:
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu8")
            break

        case 8:
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu9")
            break

        }

    }

    function updateLedEffectFolder()
    {
        switch(root.currentGroupIndex)
        {
        case 0:
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu1")
            break

        case 1:
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu2")
            break

        case 2:
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu3")
            break

        case 3:
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu4")
            break

        case 4:
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu5")
            break

        case 5:
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu6")
            break

        case 6:
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu7")
            break

        case 7:
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu8")
            break

        case 8:
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu9")
            break

        }
    }


    function refreshModel()
    {
        theTimeSlotModel.list = returnTimeSlotList()
        if(theTimeSlotModel.list.count() === 0 || currentTimeSlotIndex == -1)
        {
            root.enabled = false
        }
        else
        {
            root.enabled = true
        }
    }

    function updateCurrentConfiguration()
    {
        root.currentValveModeIndex = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex, "ValveMode")
        root.currentValveSpeed = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"ValveSpeed")
        root.currentLedSpeed = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedSpeed")
//        root.currentLedMode = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedModeHihi")
        root.currentLedColorList = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LEDValuesList")

        ledSyncSwitch.checked = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedSync")
        valveModeComboBox.currentIndex = root.currentValveModeIndex


        colorBoxesRepeater.itemAt(0).color = returnColor(0)
        colorBoxesRepeater.itemAt(1).color = returnColor(1)
        valveForceRepeatCheckBox.checked = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"ValveForceRepeat")
        valveForceRepeatSpinbox.value = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"ValveForceRepeatTimes")


        ledBuiltInEffectsCheckBox.checked = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"UseLedBuiltInEffects")
        if(ledBuiltInEffectsCheckBox.checked)
        {

            ledModeCombobox.currentIndex = setBuiltInLedMode(theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedModeName"))
        }
        else
        {
            console.trace()
            console.log("Led Mode Name: " +theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedModeName") )
            ledModeCombobox.currentIndex = root.setExternalLedMode(theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedModeName"))
        }

        ledForceRepeatCheckBox.checked = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedForceRepeat")
        ledForceRepeatTimesSpinbox.value = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedForceRepeatTimes")

        //        theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"UseLedBuiltInEffects",ledBuiltInEffectsCheckBox.checked)

        //        if(!ledBuiltInEffectsCheckBox.checked)
        //        {
        //            theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedBinPath", ledEffectFolderModel.get(ledModeCombobox.currentIndex),"filePath")
        //            theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedForceRepeat",ledForceRepeatCheckBox.checked)
        //            theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedForceRepeatTimes",ledForceRepeatTimesSpinbox.value)
        //        }

           console.log("external - ledModeComboBox current index " + ledModeCombobox.currentIndex)
    }


    function setBuiltInLedMode( modeName)
    {
        for(var i = 0; i < ledModeModel.count; i++)
        {
            if(ledModeModel.get(i).name === modeName)
                return i
        }

        return -1
    }

    function setExternalLedMode(modeName)
    {
        return ledModeCombobox.find(modeName)

    }

    onCurrentGroupIndexChanged: {

        root.groupIndexJustChanged = true
        console.log("timeSlotMGroupChanged")
        refreshModel()


        valveModeComboBox.model = returnValveModeList()
        root.updateValveEffectFolder()
        root.updateLedEffectFolder()

        if(root.currentGroupIndex == 0 || root.currentGroupIndex == 3 || root.currentGroupIndex ==5 && valveModeComboBox.currentText === "Solid")
        {
            valveControlPane.state = "Solid"
        }
        else if (valveModeComboBox.currentText === "Fade")
        {
            valveControlPane.state = "Fade"
        }
        else if(valveModeComboBox.currentText === "Blink")
        {
            valveControlPane.state = "Blink"
        }
        else
        {
            valveControlPane.state = "Default"
        }

        console.log("Group: " + root.currentGroupIndex + " - timeslot: " + root.currentTimeSlotIndex
                    + " - valveMode: " +theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex, "ValveMode") )

        root.updateCurrentConfiguration()

    }

    onCurrentTimeSlotIndexChanged:
    {
        //        refreshModel()

        //        if(root.groupIndexJustChanged)
        //        {
        //            root.groupIndexJustChanged = false
        //            console.trace()
        //            console.log("onCurrentTimeSlotIndexChanged")
        //            console.log("Group: " + root.currentGroupIndex + " - timeslot: " + root.currentTimeSlotIndex
        //                        + " - valveMode: " +theTimeSlotModel.getDataPerIndex(0, "ValveMode") )

        //            root.currentValveModeIndex = theTimeSlotModel.getDataPerIndex(0, "ValveMode")
        //        }
        //        else
        //        {

        //        if(root.groupIndexJustChanged)
        //        {
        //            root.groupIndexJustChanged = false
        //            return
        //        }
        console.trace()
        console.log("onCurrentTimeSlotIndexChanged")
        console.log("Group: " + root.currentGroupIndex + " - timeslot: " + root.currentTimeSlotIndex
                    + " - valveMode: " +theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex, "ValveMode") )

        root.updateCurrentConfiguration()



    }

    function returnTimeSlotList()
    {
        switch(root.currentGroupIndex)
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

    function returnValveModeList()
    {
        switch(root.currentGroupIndex)
        {
        case 0:
            return inverterModeModel

        case 1:
            return 0

        case 2:
            return 0

        case 3:
            return inverterModeModel

        case 4:
            return 0

        case 5:
            return inverterModeModel

        case 6:
            return 0

        case 7:
            return 0

        case 8:
            return 0

        }
    }

    Column{
        anchors.fill: parent

        TabBar{
            id: tabBar
            width: root.width
            height: 40

            TabButton{
                text: "LED"
            }
            TabButton
            {
                text: "Valve"
            }
        }
        SwipeView{
            id: swipeView
            currentIndex: tabBar.currentIndex
            clip: true
            width: root.width
            height: root.height - 40

            Pane {

                width: swipeView.width
                height: swipeView.height
                Column {
                    id: ledControlColumn
                    spacing: 15
                    width: parent.width

                    Row
                    {
                        spacing: 30
                        Button{
                            text: "Update"
                            width: 180
                            onClicked:{
                                //                                refreshModel()
                                console.trace()
                                console.log("file LED effect size: " + ledEffectFolderModel.get(ledModeCombobox.currentIndex,"fileSize"))
                                console.log("Group: " + root.currentGroupIndex + " - timeslot Id: " + root.currentTimeSlotIndex)

                                theTimeSlotModel.list = returnTimeSlotList()

                                if(ledForceRepeatCheckBox.checked)
                                {
                                    switch(root.currentGroupIndex)
                                    {
                                        // 1 mau`
                                    case 0:
                                    case 1:
                                    case 2:
                                    case 3:
                                    case 4:
                                        var currentFromMs = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"FromMs")
                                        var newToMs = ledEffectFolderModel.get(ledModeCombobox.currentIndex,"fileSize")/3 * ledForceRepeatTimesSpinbox.value * 50 *(51- ledSpeedSpinBox.value) +currentFromMs

                                        break

                                        // 2 mau
                                    case 5:
                                    case 6:
                                    case 8:

                                        currentFromMs = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"FromMs")
                                        newToMs = ledEffectFolderModel.get(ledModeCombobox.currentIndex,"fileSize")/6 * ledForceRepeatTimesSpinbox.value * 50 *(51- ledSpeedSpinBox.value) +currentFromMs
                                        break

                                        //8 mau
                                    case 7:
                                        currentFromMs = theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"FromMs")
                                        newToMs = ledEffectFolderModel.get(ledModeCombobox.currentIndex,"fileSize")/24 * ledForceRepeatTimesSpinbox.value * 50 *(51- ledSpeedSpinBox.value) +currentFromMs
                                        break
                                    }

                                    if(newToMs > theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"ToMs"))
                                    {
                                        messageDialog.title = "LED - Forced Repeat Error"
                                        messageDialog.text = "Timeslot out of range! \n Please extend the time slot until :"+ root.returnDurationString(newToMs)+" \nor change valve speed, repeat time"
                                        messageDialog.icon = MessageDialog.Warning
                                        messageDialog.open()

                                        return
                                    }
                                }

                                theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LEDValuesList", colorBoxesRepeater.itemAt(0).color +";"+colorBoxesRepeater.itemAt(1).color)
                                theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedModeName", ledModeCombobox.currentText)
                                theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedSpeed", ledSpeedSpinBox.value)

                                //                                    console.log("Led Mode: " + ledModeCombobox.currentIndex)
                                theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedModeHihi", ledModeCombobox.currentIndex)
                                theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedSync", ledSyncSwitch.checked)

                                theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"UseLedBuiltInEffects",ledBuiltInEffectsCheckBox.checked)

                                if(!ledBuiltInEffectsCheckBox.checked)
                                {
                                    theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedBinPath", ledEffectFolderModel.get(ledModeCombobox.currentIndex,"filePath"))
                                    theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedForceRepeatTimes",ledForceRepeatTimesSpinbox.value)
                                    theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedForceRepeat",ledForceRepeatCheckBox.checked)

                                }
                                else
                                {
                                    theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedForceRepeat",false)
                                }

                                if(ledForceRepeatCheckBox.checked)
                                {
                                    theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"ToMs",newToMs)
                                }

                            }
                        }
                        CheckBox{
                            id: ledBuiltInEffectsCheckBox
                            text: "Built-in Effects"
                            checked: false

                            onCheckedChanged: {
                                if(checked)
                                {
                                    ledForceRepeatCheckBox.checked = false
                                    theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedForceRepeat",ledForceRepeatCheckBox.checked)
                                    ledModeCombobox.model = ledModeModel
                                    ledModeCombobox.textRole = "name"
                                    ledModeCombobox.currentIndex = setBuiltInLedMode(theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedModeName"))
                                }
                                else
                                {
                                    ledModeCombobox.model = ledEffectFolderModel
                                    ledModeCombobox.textRole = "fileName"
                                    ledModeCombobox.currentIndex = setExternalLedMode(theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedModeName"))

                                }
                            }
                        }
                    }



                    Row{
                        spacing: 5



                        Text {

                            text: qsTr("Mode: ")
                            anchors.verticalCenter: parent.verticalCenter

                        }
                        ComboBox{
                            id: ledModeCombobox
                            model: ledBuiltInEffectsCheckBox.checked? ledModeModel : ledEffectFolderModel
                            textRole: ledBuiltInEffectsCheckBox.checked? "name" : "fileName"
                            anchors.verticalCenter: parent.verticalCenter




                        }

                        Text {

                            text: qsTr("|| Speed:")
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        SpinBox{
                            id: ledSpeedSpinBox
                            from: -50
                            to: 50
                            stepSize: 1
                            value: root.currentLedSpeed
                            editable: true
                        }

                    }

                    Row
                    {
                        spacing: 5
                        Text {

                            text: qsTr("Sync:")
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Switch{
                            id: ledSyncSwitch
                            text: ""

                        }
                        Text {

                            text: qsTr("|| Forced Repeat: ")
                            anchors.verticalCenter: parent.verticalCenter
                            visible: !ledBuiltInEffectsCheckBox.checked
                        }
                        CheckBox{
                            id: ledForceRepeatCheckBox
                            text: ""
                            visible: !ledBuiltInEffectsCheckBox.checked

                            onCheckedChanged: {
                                if(checked)
                                {
                                    valveForceRepeatCheckBox.checked = false
                                    valveForceRepeatCheckBox.enabled = false

                                    theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"ValveForceRepeat",false)
                                }
                                else
                                {
                                    valveForceRepeatCheckBox.enabled = true
                                }
                            }
                        }
                        Text {

                            text: qsTr("|| Repeat:")
                            anchors.verticalCenter: parent.verticalCenter
                            visible: !ledBuiltInEffectsCheckBox.checked
                        }

                        SpinBox{
                            id: ledForceRepeatTimesSpinbox
                            from: 1
                            to: 10000
                            stepSize: 1
                            editable: true
                            visible: !ledBuiltInEffectsCheckBox.checked
                        }


                        Text {

                            text: qsTr("Color: ")
                            anchors.verticalCenter: parent.verticalCenter
                            visible: ledBuiltInEffectsCheckBox.checked
                        }

                        Repeater{

                            id: colorBoxesRepeater
                            model: 2

                            property int  currentSelectedIndex: -1

                            Rectangle{
                                id: theColorBox
                                visible: ledBuiltInEffectsCheckBox.checked
                                property int  theIndex: index
                                width: 30
                                height: 30
                                anchors.verticalCenter: parent.verticalCenter

                                //                                radius: 15
                                color: root.returnColor(theColorBox.theIndex)
                                border.width: 1
                                border.color: "black"

                                MouseArea{
                                    anchors.fill: parent

                                    onClicked: {

                                        colorBoxesRepeater.currentSelectedIndex = theColorBox.theIndex

                                        theColorDialog.open()
                                        console.log(colorBoxesRepeater.currentSelectedIndex)
                                        theColorDialog.color = theColorBox.color
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Flickable{

                contentWidth: swipeView.width
                contentHeight: valveControlPane.implicitHeight + 100
                ScrollBar.vertical: ScrollBar{ policy: ScrollBar.AlwaysOn}

                Pane {

                    id: valveControlPane
                    width: root.width
                    state: "Default"




                    Column {
                        spacing: 40

                        Row
                        {
                            id: valveControlMode
                            spacing: 2

                            Button{
                                text: "Update"

                                onClicked: root.updateValveData()

                            }


                            Text {

                                text: qsTr("|| Mode: ")
                                anchors.verticalCenter: parent.verticalCenter

                            }
                            ComboBox{
                                id: valveModeComboBox
                                model: inverterModeModel
                                anchors.verticalCenter: parent.verticalCenter
                                textRole: "name"
                                currentIndex: root.currentValveModeIndex

                                onCurrentTextChanged: {
                                    if(currentText == "Solid")
                                    {
                                        valveControlPane.state = "Solid"
                                    }
                                    else if (currentText == "Fade")
                                    {
                                        valveControlPane.state = "Fade"
                                    }
                                    else if(currentText == "Blink")
                                    {
                                        valveControlPane.state = "Blink"
                                    }
                                    else
                                    {
                                        valveControlPane.state = "Default"
                                    }
                                }
                            }

                            Text {

                                text: qsTr("|| Speed:")
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            SpinBox{
                                id: speedValveSpinBox
                                from: -50
                                to: 50
                                stepSize: 1
                                value: root.currentValveSpeed
                                editable: true

                            }
                        }

                        Row
                        {
                            spacing: 10
                            CheckBox
                            {
                                id: valveForceRepeatCheckBox
                                text: "Forced Repeat    || "


                                onCheckedChanged: {
                                    if(checked)
                                    {
                                        ledForceRepeatCheckBox.checked = false
                                        ledForceRepeatCheckBox.enabled = false
                                        theTimeSlotModel.setDataPerIndex(root.currentTimeSlotIndex,"LedForceRepeat",false)
                                    }
                                    else
                                    {
                                        ledForceRepeatCheckBox.enabled = true
                                    }
                                }
                            }

                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("Repeat:")
                            }

                            SpinBox{
                                id: valveForceRepeatSpinbox
                                from: 1
                                to:10000
                                stepSize: 1
                                editable: true
                            }
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("times")
                            }

                            //                            TextField{
                            //                                id: valveRepeatTimeTextField
                            //                                width: 200
                            //                                validator: IntValidator{bottom: 0; top: 100000}

                            //                            }
                        }

                    }

                }

            }
        }

    }


    ListModel{
        id: inverterModeModel

        ListElement{
            name: "Solid"
        }
        ListElement{
            name: "Fade"
        }
        ListElement{
            name: "Blink"
        }
    }

    ListModel{
        id: valveBlinkModeModel

        ListElement{
            name: "Immediate"
        }
        ListElement{
            name: "Transition"
        }
    }


    ListModel{
        id: ledModeModel

        ListElement{
            name:"Color Transition"
        }
        ListElement{
            name: "Solid"
        }
        ListElement{
            name: "Blink"
        }
        ListElement{
            name:"Fade In/Out"
        }
        //        ListElement{
        //            name:"Strobe"
        //        }

    }

    FolderListModel{
        id: valveEffectFolderModel
        nameFilters: ["*.bin"]
        showDirs: false
        showDotAndDotDot: false
        rootFolder: Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects")



        Component.onCompleted:
        {
            console.trace()
            console.log("Folder count: " + valveEffectFolderModel.count)
            //           valveEffectFolderModel. = Qt.resolvedUrl("file:///"+appFilePath+"/Effects")
            valveEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/ValveEffects/Kieu1")

        }

        onFolderChanged: {
            console.log("Folder count: " + valveEffectFolderModel.count)
            valveModeComboBox.model = valveEffectFolderModel
            valveModeComboBox.textRole = "fileName"

            valveModeComboBox.currentIndex = root.currentValveModeIndex

        }

    }

    FolderListModel{
        id: ledEffectFolderModel
        nameFilters: ["*.bin"]
        showDirs: false
        showDotAndDotDot: false
        rootFolder: Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects")



        Component.onCompleted:
        {
//            console.trace()
//            console.log("Folder count: " + ledEffectFolderModel.count)
//            //           valveEffectFolderModel. = Qt.resolvedUrl("file:///"+appFilePath+"/Effects")
            ledEffectFolderModel.folder = Qt.resolvedUrl("file:///"+appFilePath+"/LedEffects/Kieu1")

        }

        onFolderChanged: {
            console.log("Folder count: " + ledEffectFolderModel.count)
            if(ledBuiltInEffectsCheckBox.checked)
            {

                ledModeCombobox.currentIndex = setBuiltInLedMode(theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedModeName"))
            }
            else
            {
//                console.trace()
//                console.log("Led Mode Name: " +theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedModeName") )
                ledModeCombobox.currentIndex = root.setExternalLedMode(theTimeSlotModel.getDataPerIndex(root.currentTimeSlotIndex,"LedModeName"))
            }

        }

    }

    ColorDialog
    {
        id: theColorDialog

        title: "Please choose a color"

        onAccepted: {
            colorBoxesRepeater.itemAt(colorBoxesRepeater.currentSelectedIndex).color = theColorDialog.color
            console.trace()
            console.log("the color: " + theColorDialog.color)
        }

        onRejected: {

        }
    }

    MessageDialog{
        id: messageDialog
    }


}
