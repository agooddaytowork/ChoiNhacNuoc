import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

Item {

    id: root
    property string  currentPortName: appSetting.portName

    Settings{
        id: appSetting
        property string portName: ""
        property bool serialOutputState: false
    }

    function open()
    {
        console.log(appSetting.portName)
        theSerialDialog.open()

        theSerialPortNamesModel.clear()

        theInterfaceGod.refreshSerialPorts()

        var currentPortIndex = 0;

        for(var i = 0; i < theInterfaceGod.getSerialPortCount(); i++)
        {
            theSerialPortNamesModel.append({ PortName: theInterfaceGod.getSerialPortNames(i)})

            if(root.currentPortName === theInterfaceGod.getSerialPortNames(i) )
            {
                currentPortIndex = i
            }
        }

        serialComboBox.currentIndex = currentPortIndex
    }
    function close()
    {
        theSerialDialog.close()
    }

    ListModel{
        id: theSerialPortNamesModel
    }



    Dialog{
        id: theSerialDialog
        x: (parent.width - width) / 2
        y: (parent.height - height) / 4
        modal: true
        focus: true
        implicitHeight: 300
        implicitWidth:  300



        title: "Serial ports "
        closePolicy: Popup.NoAutoClose

        footer: DialogButtonBox{


            Button
            {
                text: qsTr("Close")
                DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
            }
        }

        Column{
            spacing: 2
            ComboBox{
                anchors.centerIn: parent.Center

                id: serialComboBox
                model: theSerialPortNamesModel
                textRole: "PortName"
            }

            Row
            {
                spacing: 2
                Button{
                    text: "Connect"
                    onClicked: {
                        theInterfaceGod.connectSerialPort(serialComboBox.currentText)

                        root.currentPortName = serialComboBox.currentText
                        appSetting.portName = serialComboBox.currentText
                    }
                }

//                Button{
//                    text: "Disconnect"

//                    onClicked: {
//                        theInterfaceGod.disconnectSerialPort()
//                    }
//                }
            }
        }



        onAccepted:
        {
            theSerialDialog.close()
        }



    }


}
