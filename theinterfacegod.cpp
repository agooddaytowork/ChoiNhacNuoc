#include "theinterfacegod.h"

theInterfaceGod::theInterfaceGod(QObject *parent) : QObject(parent), mSerialPortCount(0)
{

}


void theInterfaceGod::regenerateFrameList(const int &duration, const int &frameDuration)
{

    emit SIG_regenerateFrameList(duration, frameDuration);
}

void theInterfaceGod::playFrame(const int &frameNo)
{
    static int previousFrame = 0;

    if(previousFrame != frameNo)
    {
        previousFrame = frameNo;
    emit SIG_playFrame(frameNo);
    }

}

void theInterfaceGod::invokeTimeSlotChanged(){
    emit gui_timeSLotChanged();
}

void theInterfaceGod::refreshSerialPorts()
{
    mSerialPortInfoList.clear();
    mSerialPortInfoList = QSerialPortInfo::availablePorts();

    mSerialPortCount = mSerialPortInfoList.size();
}

int theInterfaceGod::getSerialPortCount()
{
    return mSerialPortCount;
}

QString theInterfaceGod::getSerialPortNames(const int &index)
{
    if(index >= mSerialPortInfoList.size())
    {
        return "";
    }
    return mSerialPortInfoList.at(index).portName();
}


void theInterfaceGod::reportError(const QString &title, const QString &content)
{
    QMessageBox::warning(nullptr,title,content);
}

void theInterfaceGod::closeApplication()
{
    emit gui_CloseApplication();
}

void theInterfaceGod::reportInformation(const QString &title, const QString &content)
{
    QMessageBox::information(nullptr,title,content);
}

void theInterfaceGod::serialPortConnectionStatus(const bool &status)
{
    emit gui_SerialPortConnection(status);
}


void theInterfaceGod::connectSerialPort(const QString &portName)
{
    emit SIG_connectSerialPort(portName);
}


void theInterfaceGod::disconnectSerialPort()
{
    emit SIG_disconnectSerialPort();
}


void theInterfaceGod::closeThreads()
{
    emit SIG_CloseThreads();
}


void theInterfaceGod::enableSerialOutput(const bool &enable)
{
    emit SIG_enableSerialOutput(enable);
}

void theInterfaceGod::saveSession(const QString &fileName)
{
    emit SIG_saveSession(fileName);
}

void theInterfaceGod::importTimeSlotList(const QString &fileName)
{
    emit SIG_importTimeSlotList(fileName);
}

void theInterfaceGod::frameListRescontrusctedHandler()
{
    static int cnt = 0;

    cnt++;

    if(cnt == 9)
    {
        cnt = 0;
        emit gui_FrameListResconstructed();

    }
}

void theInterfaceGod::clearTimeSlotList()
{
    emit SIG_clearTimeSlotList();
}

void theInterfaceGod::sendSerialStopFrame()
{
    emit SIG_sendSerialStopFrame();
}
