import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtMultimedia 5.9
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.2



ApplicationWindow {

    id: root
    visible: true
    width: 1366
    height: 768
    title: qsTr("Nhạc nước Tiền Giang")
    property int  fromMs: 0
    property int toMs: 60000
    property int  duration: 0
    property int  currentPosition: 0
    property int  buttonSize: 40
    property bool currentSongJustChanged: false
    property bool  playMusic: false
    property string currentSong: ""
    property bool  repeatList: false
    property bool repeatOne: false



    function playMusicAction(musicIndex)
    {
        root.currentSong = musicListModel.get(musicIndex).name
        root.currentPosition = 0
        root.duration = 0
        audioPlayer.source = musicListModel.get(musicIndex).filePath
        theInterfaceGod.clearTimeSlotList()
        root.playMusic = true
        musicListView.currentPlayedIndex = musicIndex


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

    onCurrentSongChanged: {

        console.trace()
        root.currentSongJustChanged = true
        //        console.log("file:///"+appFilePath+"/Sessions/" + root.currentSong +".bin")
        //        theInterfaceGod.importTimeSlotList("file:///"+appFilePath+"/Sessions/" + root.currentSong +".bin")
    }

    /***** THIS SHIT IS FOR QUITING THE Application after closing the GOODDDAAM THREAD ****/
    onClosing:
    {
        close.accepted = false;

        theInterfaceGod.closeThreads()
    }

    Connections{
        target: theInterfaceGod

        onGui_CloseApplication:
        {
            Qt.quit()
        }


        onGui_timeSLotChanged:
        {
            if(root.playMusic)
            {
//                root.playMusic = false
                audioPlayer.seek(root.currentPosition)
                audioPlayer.play()
                root.duration = audioPlayer.duration
            }
        }


        onGui_SerialPortConnection:
        {
            if(isConnected)
            {
                serialOutPutCheckBox.enabled = true
            }
            else
            {
                serialOutPutCheckBox.checked = false
                serialOutPutCheckBox.enabled = false
            }
        }

        onGui_FrameListResconstructed:
        {
            console.trace()
            if(root.currentSongJustChanged)
            {
                root.currentSongJustChanged = false

                theInterfaceGod.importTimeSlotList("file:///"+appFilePath+"/Sessions/" + root.currentSong +".bin")
            }
        }
    }

    /***** THIS SHIT IS FOR QUITING THE Application after closing the GOODDDAAM THREAD ****/



    onCurrentPositionChanged:
    {

    }

    header: ToolBar{



        Row{
            anchors.top: parent.top
            anchors.left: parent.left
            height: parent.height
            ToolButton{
                text: "File"
                visible: false
                onClicked: {
                    fileMenu.open()
                }

                Menu{
                    id: fileMenu
                    y: parent.height

                    MenuItem{

                        text: "Open music"
                        onClicked: {
                            theFileDialog.open()
                        }
                    }
                    MenuItem{

                        text: "Add music"
                        onClicked: {
                            addMusicDialog.open()
                        }
                    }
                    MenuItem{

                        text: "New Session"
                        onClicked: {
                            root.currentSong = ""
                            root.currentPosition = 0
                            root.duration = 0

                            audioPlayer.source = ""
                            //                            root.currentPosition = 0
                            //                            root.duration = 0
                            theInterfaceGod.clearTimeSlotList()

                        }
                    }
                    MenuItem{

                        text: "Save Session"
                        onClicked: {
                            theInterfaceGod.saveSession(root.currentSong)
                        }
                    }
                    MenuItem{

                        text: "Import Session"
                        onClicked: {

                            importFileDialog.open()

                        }
                    }
                    MenuItem{

                        text: "Export Session"
                        onClicked: {

                        }
                    }
                }

            }

            ToolSeparator
            {
                visible: false
            }


            Button
            {
                icon.name: "Play"
                icon.source: "icons/play.png"
                width: root.buttonSize
                height: root.buttonSize
                icon.color: "transparent"
                icon.height: root.buttonSize
                icon.width: root.buttonSize
                onClicked: {
                    //                    mainTimer.start()

                    if(root.currentSong !== musicListModel.get(musicListView.currentPlayedIndex).name)
                    {

                        root.playMusicAction(musicListView.currentPlayedIndex)


                    }

                    root.playMusic = true
                    timeIndicator.autoPlay = true
                    audioPlayer.seek(root.currentPosition)
                    audioPlayer.play()

                    timeIndicator.movable = false
                    root.duration = audioPlayer.duration

                }

            }

            Button
            {
                icon.name: "Pause"
                icon.source: "icons/pause.png"
                width:  root.buttonSize
                height: root.buttonSize
                icon.color: "transparent"
                icon.height: root.buttonSize
                icon.width: root.buttonSize
                onClicked: {
                    audioPlayer.pause()
                    timeIndicator.autoPlay = false

                    //                    mainTimer.stop()

                }

            }

            Button
            {
                icon.name: "Stop"
                icon.source: "icons/stop.png"
                width:  root.buttonSize
                height: root.buttonSize
                icon.color: "transparent"
                icon.height: root.buttonSize
                icon.width: root.buttonSize
                onClicked: {
                    timeIndicator.autoPlay = false
                    //                    mainTimer.stop()
                    root.currentPosition = 0
                    root.playMusic = false
                    audioPlayer.stop()
                }
            }
            Button{
                icon.name: "Back"
                icon.source: "icons/back.png"
                width:  root.buttonSize
                height: root.buttonSize
                icon.color: "transparent"
                icon.height: root.buttonSize
                icon.width: root.buttonSize
                onClicked: {
                    for(var i = musicListView.currentPlayedIndex-1 ; i >=0 ; i--)
                    {
                        if(musicListModel.get(i).sessionAvailable !== false)
                        {
                            root.playMusicAction(i)
                            return
                        }
                    }
                    for( i = musicListView.count-1; i >=0; i--)
                    {
                        if(musicListModel.get(i).sessionAvailable !== false)
                        {
                            root.playMusicAction(i)
                            return
                        }
                    }


                }

            }

            Button{
                icon.name: "Next"
                icon.source: "icons/next.png"
                width:  root.buttonSize
                height: root.buttonSize
                icon.color: "transparent"
                icon.height: root.buttonSize
                icon.width: root.buttonSize
                onClicked: {
                    for(var i = musicListView.currentPlayedIndex +1; i< musicListModel.count; i++)
                    {
                        if(musicListModel.get(i).sessionAvailable !== false)
                        {
                            root.playMusicAction(i)
                            return
                        }
                    }
                    for(i = 0; i < musicListModel.count; i++)
                    {
                        if(musicListModel.get(i).sessionAvailable !== false)
                        {
                            root.playMusicAction(i)
                            return
                        }
                    }
                }
            } Button{
                icon.name: "Repeat"
                icon.source: root.repeatList?  "icons/repeatGreen.png" :"icons/repeatBlack.png"
                width:  root.buttonSize
                height: root.buttonSize
                icon.color: "transparent"
                icon.height: root.buttonSize
                icon.width: root.buttonSize
                onClicked: {
                    root.repeatList = !root.repeatList
                    if(root.repeatList)
                    {
                        root.repeatOne = false
                    }
                }
            }

            Button{
                icon.name: "Repeat One"
                icon.source: root.repeatOne?  "icons/oneRepeatGreen.png" :"icons/oneRepeatBlack.png"
                width:  root.buttonSize
                height: root.buttonSize
                icon.color: "transparent"
                icon.height: root.buttonSize
                icon.width: root.buttonSize
                onClicked: {
                    root.repeatOne = !root.repeatOne

                    if(root.repeatOne)
                    {
                        root.repeatList = false
                    }
                }
            }
            Button{
                icon.name: "Speaker"
                icon.source: "icons/speaker.png"
                width:  root.buttonSize
                height: root.buttonSize
                icon.color: "transparent"
                icon.height: root.buttonSize
                icon.width: root.buttonSize
            }
            Slider{
                id: volumeSlider
                from: 0.0
                to: 1.0
                stepSize: 0.05

                value: 1.0

                onValueChanged: {
                    audioPlayer.volume = value
                }
            }
            Button{
                icon.name: "Mute"
                icon.source: audioPlayer.muted ? "icons/mute.png" : "icons/muteBlack.png"
                width:  root.buttonSize
                height: root.buttonSize
                icon.color: "transparent"
                icon.height: root.buttonSize
                icon.width: root.buttonSize
                onClicked: {

                    audioPlayer.muted = !audioPlayer.muted
                }
            }
        }



        Row
        {
            anchors.right: parent.right
            anchors.top: parent.top
            height: parent.height
            anchors.rightMargin: 10
            spacing: 2
            Label{
                id: songLabel
                anchors.verticalCenter: parent.verticalCenter
                text: "Song: " + root.currentSong
            }

            ToolSeparator{

            }

            Label{
                id: timeLabel
                text: root.returnDurationString(root.currentPosition)
                anchors.verticalCenter: parent.verticalCenter


            }



            ToolSeparator{

            }

            CheckBox{
                id: serialOutPutCheckBox
                enabled: false
                text: "Output"

                onCheckedChanged: {
                    theInterfaceGod.enableSerialOutput(checked)
                }
            }
            Button{
                id: serialButton
                text: "Serial: "
                width: 60

                onClicked: {
                    theSerialDialog.open()
                }
            }
            Label{
                id: serialPortNameText
                text: theSerialDialog.currentPortName
                anchors.verticalCenter: parent.verticalCenter
            }
        }

    }

    Grid{
        id: mainGrid
        enabled: true
        rows: 1
        columns: 2
        anchors.fill: parent
        rowSpacing: 1
        columnSpacing: 1


        Rectangle{
            id: controlTimeLineBGRec
            color: "white"
            width: root.width-500
            height: root.height
            visible: false


            TimeIndicator{

                id: timeIndicator

                height: parent.height / 10 * 9
                width: parent.width / 10 * 9
                anchors.left: parent.left
                anchors.leftMargin: parent.width/10
                anchors.top: parent.top
                anchors.topMargin: 5
                z:3
                fromMs: root.fromMs
                toMs: root.toMs
                duration: root.duration
                position: root.currentPosition

                onTimeIndicatorPositionChanged:
                {


                    if(audioPlayer.playbackState == Audio.PlayingState)
                    {
                        audioPlayer.seek(mYposition)
                    }
                    else
                    {
                        root.currentPosition = mYposition
                    }

                    var frameNo = mYposition/  50

                    // console.log("frame Point: " + frameNo)
                    theInterfaceGod.playFrame(parseInt(frameNo))
                }
                onChangeFromAndToMoment: {
                    root.fromMs = from
                    root.toMs = to
                }

            }

            TimeLegend{
                id: timeLegend
                width: parent.width / 10 * 9
                anchors.left: parent.left
                anchors.leftMargin: parent.width/10
                anchors.top: parent.top
                anchors.topMargin: 20
                height: 20
                anchors.right: parent.right
                miniTick: 2
                tick: 15
                fromMs: root.fromMs
                toMs: root.toMs


                onRequestTimeIndicatorPosition: {


                    if(audioPlayer.playbackState == Audio.PlayingState)
                    {
                        audioPlayer.seek(position)
                    }
                    else
                    {
                        root.currentPosition = position
                    }

                    var frameNo = position/  50

                    // console.log("frame Point: " + frameNo)
                    theInterfaceGod.playFrame(parseInt(frameNo))


                }

                Connections
                {
                    target: root

                    onFromMsChanged:
                    {
                        timeLegend.fromMs = root.fromMs
                    }

                    onToMsChanged:
                    {
                        timeLegend.toMs = root.toMs
                    }
                }
            }
            Column{
                anchors.top: parent.top
                anchors.topMargin: 40
                width: parent.width
                height: parent.height - 40  - 30
                spacing: 2


                Repeater{
                    id: groupControlPanelRepeater
                    property int  currentGroupIndex: 0
                    property int  currentTimeSlotIndex: 0

                    model: 9
                    delegate: GroupControlPanel{
                        id: groupControlPanelDelegate
                        width: parent.width
                        groupIndex: index
                        height: (parent.height -40 - 2*9)/9
                        fromMs: root.fromMs
                        toMs: root.toMs
                        duration: root.duration
                        selected: {
                            if(groupControlPanelRepeater.currentGroupIndex === groupControlPanelDelegate.groupIndex)
                            {
                                true
                            }
                            else
                            {
                                false
                            }
                        }
                        onTimeSlotSelect:
                        {
                            groupControlPanelRepeater.currentTimeSlotIndex = timeSlotIndex
                            groupControlPanelRepeater.currentGroupIndex = groupControlPanelDelegate.groupIndex

                            //                            timeLineSlotControlBox.refreshModel()

                        }

                        onChangeFromAndToMoment:
                        {
                            root.fromMs = from
                            root.toMs = to
                        }
                        onTimeLineSelected: {
                            groupControlPanelRepeater.currentTimeSlotIndex = 0
                            groupControlPanelRepeater.currentGroupIndex = groupIndex

                        }

                        onTimeSlotAdded: {

                            groupControlPanelRepeater.currentGroupIndex = groupControlPanelDelegate.groupIndex
                            groupControlPanelRepeater.currentTimeSlotIndex = timeSlotIndex


                            timeLineSlotControlBox.refreshModel()
                        }

                        onTimeSlotRemoved: {

                            timeLineSlotControlBox.refreshModel()
                        }

                        onUpdateAllTimeSlots: {

                        }

                    }
                }
            }

            TimeLineScroll{
                id: timeLineScrol
                width: parent.width / 10 * 9
                anchors.left: parent.left
                anchors.leftMargin: parent.width/10
                height: 40
                duration: root.duration
                fromMs: root.fromMs
                toMs: root.toMs
                z:2
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                onChangeFromAndToMoment:
                {
                    root.fromMs = from
                    root.toMs = to
                }
            }

            TimeIndicator{

                id: timeIndicatorForScrollBar

                height: (parent.height -5) / 11
                width: parent.width / 10 * 9
                anchors.left: parent.left
                anchors.leftMargin: parent.width/10
                anchors.bottom: parent.bottom
                z:3
                fromMs:0
                toMs: root.duration
                duration: root.duration
                position: root.currentPosition
            }
        }
        Rectangle{

            id: presenterBGRec
            color: "#474747"
            border.width: 1
            border.color: "black"
            width: 750
            height: root.height


            Rectangle{
                width: parent.width
                anchors.top: parent.top
                anchors.left: parent.left
                height: parent.height
                color: "#474747"
                border.width: 1
                border.color: "black"
                Repeater{
                    model: 9
                    delegate: MusicPresenterGroup{
                        id: theGroup

                        property int groupIndex: index
                        groupID: index
                        scale: 1.8
                    }
                }

                Label{

                    text: returnDurationString(root.currentPosition)
                    color: "white"
                    font.pointSize: 15
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.rightMargin: 80
                    anchors.bottomMargin: 80
                }

                Slider{
                    id: durationSlider
                    from: root.fromMs
                    to: root.toMs
                    value: root.currentPosition
                    stepSize: 1
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 40
                    width: parent.width - 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    enabled: root.toMs == 0? false : true

                    onValueChanged: {
                        if(durationSlider.pressed)
                        {
                            audioPlayer.seek(value)
                            root.currentPosition = value
                        }
                    }

                }

            }
            TimeLineSlotControlBox{

                id: timeLineSlotControlBox
                visible: false
                width: parent.width
                height: root.height-500
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                currentGroupIndex: groupControlPanelRepeater.currentGroupIndex
                currentTimeSlotIndex:  groupControlPanelRepeater.currentTimeSlotIndex


            }


        }


        Rectangle{
            width: parent.width - 750
            height: parent.height
            color: "grey"


            ListView{
                id: musicListView
                anchors.fill: parent


                model: musicListModel
                property int  currentPlayedIndex: 0

                header: Rectangle{
                    width: parent.width
                    anchors.top: parent.top
                    anchors.left: parent.left
                    height: 50
                    Label{
                        text: "Play List"
                        anchors.centerIn: parent
                        font.bold: true
                        font.pointSize: 15
                    }

                    Button{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        text: "Add Music"

                        onClicked: {
                            addMusicDialog.open()
                        }
                    }
                }

                delegate: MouseArea{
                    id: musicItemDelegate
                    width: parent.width
                    height: 50


                    enabled: sessionAvailable


                    drag.target: dragMusicItem

                    property int visualIndex: index

//                    onClicked: {
//                        musicListView.currentPlayedIndex = musicItemDelegate.visualIndex
//                    }

                    onDoubleClicked: {

                        root.playMusicAction(musicItemDelegate.visualIndex)


                    }

                    Rectangle{
                        id: dragMusicItem
                        width: parent.width
                        height: 50
                        color: musicListView.currentPlayedIndex == musicItemDelegate.visualIndex? "orange" :"white"

                        anchors {
                            horizontalCenter: parent.horizontalCenter;
                            verticalCenter: parent.verticalCenter
                        }
                        Label{
                            text: name
                            anchors.left: parent.left
                            anchors.leftMargin: 120
                            anchors.verticalCenter: parent.verticalCenter
                            color: "black"

                        }

                        CheckBox{
                            text: "Available || "
                            checked: sessionAvailable
                            anchors.verticalCenter: parent.verticalCenter
                            checkable: false
                            onCheckedChanged:
                            {
                                checkable = false
                            }

                        }

                        Button{
                            text: "Delete"
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: 5
                            onClicked: {
                                musicListModel.remove(musicItemDelegate.visualIndex)
                            }
                        }

                        Connections{
                            target: sessionFolderListModel
                            onCountChanged: {

                                if(root.checkForSessions(name))
                                {
                                    sessionAvailable = true
                                }
                                else
                                {
                                    sessionAvailable = false
                                }

                            }
                        }

                        Drag.active: musicItemDelegate.drag.active
                        Drag.source: musicItemDelegate
                        Drag.hotSpot.x: parent.width/2
                        Drag.hotSpot.y: 25

                        states: [
                            State {
                                when: dragMusicItem.Drag.active
                                ParentChange {
                                    target: dragMusicItem
                                    parent: musicListView
                                }

                                AnchorChanges {
                                    target: dragMusicItem;
                                    anchors.horizontalCenter: undefined;
                                    anchors.verticalCenter: undefined
                                }
                            }
                        ]

                    }

                    DropArea{
                        anchors { fill: parent; margins: 15 }
                        onEntered:
                        {
                            var sourceIndex = drag.source.visualIndex
                            var targetIndex = musicItemDelegate.visualIndex


//                            musicItemDelegate.visualIndex = PreviouSsourceIndex
//                            drag.source.visualIndex = targetIndex

                            if(musicListView.currentPlayedIndex === sourceIndex)
                            {
                                musicListView.currentPlayedIndex = targetIndex
                            }
                            else if(musicListView.currentPlayedIndex === targetIndex)
                            {
                                musicListView.currentPlayedIndex = sourceIndex
                            }



                            musicListModel.move(sourceIndex, targetIndex,1)
                        }
                    }
                }
            }



        }
    }

    Timer{
        id: mainTimer
        interval: 50
        repeat: true
        running: false
        triggeredOnStart: true

        onTriggered: {
            root.currentPosition += 50
        }

    }

    Audio{
        id: audioPlayer

        autoLoad: true
        notifyInterval: 45
        property int  previousPosition: 0



        onDurationChanged: {
            console.log("changed DURATION ASLKDJALSDJSKLAJDKLSAJJD: " + duration)


            if(duration != 0)
            {
                root.duration = duration
                root.toMs = duration
                theInterfaceGod.regenerateFrameList(duration, 50)
            }


        }

        onPositionChanged: {

            // console.log("delta " + (audioPlayer.position - previousPosition))



            root.currentPosition = audioPlayer.position
            timeIndicator.deltaFromPreviousPosition = audioPlayer.position - audioPlayer.previousPosition

            audioPlayer.previousPosition = audioPlayer.position

            var frameNo = audioPlayer.position/  50

            // console.log("frame Point: " + frameNo)
            theInterfaceGod.playFrame(parseInt(frameNo))

        }

        onStopped: {
            console.trace()
            if(/*audioPlayer.playbackState == audioPlayer.StoppedState*//* && */root.playMusic)
            {
                console.log("oi dcm")
                if(root.repeatList)
                {
                    for(var i = musicListView.currentPlayedIndex +1; i< musicListModel.count; i++)
                    {
                        if(musicListModel.get(i).sessionAvailable !== false)
                        {
                            root.playMusicAction(i)
                            return
                        }
                    }
                    for(i = 0; i < musicListModel.count; i++)
                    {
                        if(musicListModel.get(i).sessionAvailable !== false)
                        {
                            root.playMusicAction(i)
                            return
                        }
                    }
                }
                else if(root.repeatOne)
                {
                        audioPlayer.play()
                }
            }
        }

        onPlaybackStateChanged: {


        }
    }

    FileDialog{
        id: theFileDialog
        folder: appFilePath
        selectMultiple: false
        selectFolder: false
        nameFilters: ["Music (*.mp3 *.wav)"]

        onAccepted: {

            theFileDialog.folder = fileUrl
            audioPlayer.source = fileUrl

            var theFileName = ""
            theFileName += fileUrl
            var newSongName = theFileName.split('\\').pop().split('/').pop().slice(0,-4);
            if(root.currentSong !== newSongName)
            {
                root.currentSong = newSongName

                root.currentPosition = 0
                root.duration = 0
                theInterfaceGod.clearTimeSlotList()
            }

        }
    }

    FileDialog{
        id: importFileDialog
        selectMultiple: false
        title: "Import Sessions"
        selectFolder: false
        nameFilters: ["text (*.txt *.bin) "]
        onAccepted: {

            console.log("file URL " +  fileUrl)

            theInterfaceGod.importTimeSlotList(fileUrl)

        }
    }

    SerialDialog{
        id: theSerialDialog
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin:  250
    }



    FileDialog{
        id: addMusicDialog
        selectMultiple:  true
        title: "Select Songs"
        selectFolder:  false
        nameFilters: ["songs (*.mp3 *.wav)"]
        onAccepted: {
            //            for

            console.log("ACcepted")
            addMusicDialog.folder = fileUrl
            var musicString =""
            musicString=    fileUrls
            console.log(fileUrls.length)
            console.log(fileUrls[0])

            //            var newSongName = theFileName.split('\\').pop().split('/').pop().slice(0,-4);

            for(var i = 0; i < fileUrls.length; i++)
            {

                if(musicListModel.count == 0)
                {
                    musicListModel.append({name: fileUrls[i].split('\\').pop().split('/').pop().slice(0,-4)
                                              , filePath: fileUrls[i]
                                              ,sessionAvailable: root.checkForSessions(fileUrls[i].split('\\').pop().split('/').pop().slice(0,-4))})
                }
                else
                {
                    var songName =""
                    songName = fileUrls[i].split('\\').pop().split('/').pop().slice(0,-4)
                    for(var ii =0; ii < musicListModel.count; ii++)
                    {



                        var songFound = false
                        console.log(musicListModel.get(ii).name)
                        if(musicListModel.get(ii).name === songName)
                        {
                            songFound = true
                            break
                        }

                    }
                    if(!songFound)
                    {
                        musicListModel.append({name: songName
                                                  , filePath: fileUrls[i]
                                                  , sessionAvailable: root.checkForSessions(songName)})
                    }

                }

            }

            console.log("music List count: " +musicListModel.count)

        }
    }

    function checkForSessions(songName)
    {

        console.trace()
        for(var ii = 0; ii < sessionFolderListModel.count; ii++)
        {
            var sessionName =  sessionFolderListModel.get(ii, "fileName").replace(".bin","")

            console.log("Song Name: " + songName)
            console.log("SessionName" + sessionName)
            if(songName === sessionName  )
            {

                return true
            }
        }
        return false;

    }

    FolderListModel{
        id: sessionFolderListModel
        nameFilters: ["*.bin"]
        showDirs: false
        showDotAndDotDot: false
        rootFolder: Qt.resolvedUrl("file:///"+appFilePath+"/Sessions")
        folder: Qt.resolvedUrl("file:///"+appFilePath+"/Sessions")



    }


    ListModel{
        id: musicListModel

    }
}
