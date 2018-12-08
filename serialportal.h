#ifndef SERIALPORTAL_H
#define SERIALPORTAL_H

#include <QObject>
#include <QSerialPort>
#include <QString>

class SerialPortal : public QObject
{
    Q_OBJECT

    QSerialPort *mSerialPort;

    void serialPortErrorHandler(QSerialPort::SerialPortError error);
public:
    explicit SerialPortal(QObject *parent = nullptr);
    bool connect(const QString &portName);
    bool isConnected() const;
    void disconnectSerialPort();
    void start();
    void sendFrame(const QByteArray &frame);



signals:

    void SIG_reportError(const QString &title, const QString &content);
    void SIG_reportInformation(const QString &title, const QString &content);
    void SIG_isConnected(const bool &status);



public slots:
};

#endif // SERIALPORTAL_H
