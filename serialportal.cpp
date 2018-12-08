#include "serialportal.h"

SerialPortal::SerialPortal(QObject *parent) : QObject(parent)
{



}

void SerialPortal::start()
{
    mSerialPort = new QSerialPort();
    mSerialPort->setBaudRate(QSerialPort::Baud38400);
    QObject::connect(mSerialPort,&QSerialPort::errorOccurred,this,&SerialPortal::serialPortErrorHandler);
    QObject::connect(mSerialPort,&QSerialPort::aboutToClose, this, [=](){ emit this->SIG_isConnected(false); });
}


void SerialPortal::sendFrame(const QByteArray &frame)
{
    static bool informedError = false;
    if(mSerialPort->isOpen())
    {
        mSerialPort->write(frame);
        informedError = false;
    }
    else
    {
        if(!informedError) emit SIG_reportError("Serial Port Error" ,"Port is not opened, cannot send data");

        informedError = true;
    }
}


bool SerialPortal::connect(const QString &portName)
{
    if(mSerialPort->portName() != portName)
    {

        if(mSerialPort->isOpen())
        {
            mSerialPort->close();
        }
        mSerialPort->setPortName(portName);

        if(mSerialPort->open(QIODevice::ReadWrite))
        {
            emit SIG_reportInformation("Serial Port","Connected to Port: " +mSerialPort->portName());
            emit SIG_isConnected(true);
            return true;
        }

    }

    return false;
}

bool SerialPortal::isConnected() const
{
    return mSerialPort->isOpen();
}

void SerialPortal::serialPortErrorHandler(QSerialPort::SerialPortError error)
{


    switch (error) {

    case QSerialPort::NoError:
        // emit SIG_reportError("Serial Port Error","No error occurred.");
        break;

    case QSerialPort::DeviceNotFoundError:
        emit SIG_reportError("Serial Port Error","DeviceNotFoundError: An error occurred while attempting to open an non-existing device.");
        emit SIG_isConnected(false);
        break;

    case QSerialPort::PermissionError:
        emit SIG_reportError("Serial Port Error","PermissionError: An error occurred while attempting to open an already opened device by another process or a user not having enough permission and credentials to open.");
        emit SIG_isConnected(false);
        break;

    case QSerialPort::OpenError:
        emit SIG_reportError("Serial Port Error","OpenError: An error occurred while attempting to open an already opened device in this object.");
        emit SIG_isConnected(false);
        break;
    case QSerialPort::NotOpenError:
        emit SIG_reportError("Serial Port Error","NotOpenError:This error occurs when an operation is executed that can only be successfully performed if the device is open. This value was introduced in QtSerialPort 5.2.");

        emit SIG_isConnected(false);
        break;
    case QSerialPort::ParityError:
        emit SIG_reportError("Serial Port Error","ParityError:Parity error detected by the hardware while reading data. This value is obsolete. We strongly advise against using it in new code");
        break;
    case QSerialPort::FramingError:
        emit SIG_reportError("Serial Port Error","FramingError: Framing error detected by the hardware while reading data. This value is obsolete. We strongly advise against using it in new code");
        break;
    case QSerialPort::BreakConditionError:
        emit SIG_reportError("Serial Port Error","BreakConditionError:Break condition detected by the hardware on the input line. This value is obsolete. We strongly advise against using it in new code.");
        break;
    case QSerialPort::WriteError:
        emit SIG_reportError("Serial Port Error","WriteError:An I/O error occurred while writing the data.");
        emit SIG_isConnected(false);

        break;
    case QSerialPort::ReadError:
        emit SIG_reportError("Serial Port Error","ReadError:An I/O error occurred while reading the data.");
        emit SIG_isConnected(false);

        break;
    case QSerialPort::ResourceError:
        emit SIG_reportError("Serial Port Error","ResourceError:An I/O error occurred when a resource becomes unavailable, e.g. when the device is unexpectedly removed from the system.");
        emit SIG_isConnected(false);

        break;
    case QSerialPort::UnsupportedOperationError:
        emit SIG_reportError("Serial Port Error","UnsupportedOperationError:The requested device operation is not supported or prohibited by the running operating system.");
        emit SIG_isConnected(false);

        break;
    case QSerialPort::TimeoutError:
        emit SIG_reportError("Serial Port Error","TimeoutError:A timeout error occurred. This value was introduced in QtSerialPort 5.2.");
        emit SIG_isConnected(false);

        break;
    case QSerialPort::UnknownError:
        emit SIG_reportError("Serial Port Error","UnknownError:An unidentified error occurred.");
        emit SIG_isConnected(false);

        break;
    }
}

void SerialPortal::disconnectSerialPort()
{
    mSerialPort->close();
}
