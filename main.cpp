#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "timeslotlist.h"
#include "timeslotmodel.h"
#include "timeslotlistexporter.h"
#include "timeslotlistimporter.h"

#include "musicpresenterlist.h"
#include "musicpresentermodel.h"
#include "presenterframelist.h"
#include "theinterfacegod.h"

#include "serialframebuffer.h"
#include "serialportal.h"

#include <QThread>
#include <QVector>
#include <QDebug>

#include <QApplication>




int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN) || defined(Q_OS_ANDROID)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    qmlRegisterType<timeSlotModel>("TimeLine", 1, 0, "TimeSlotModel");
    qmlRegisterUncreatableType<timeSlotList>("TimeLine", 1, 0, "TimeSlotList",
                                             QStringLiteral("ToDoList should not be created in QML"));

    qmlRegisterType<MusicPresenterModel>("MusicPresenter", 1, 0, "MusicPresenterModel");
    qmlRegisterUncreatableType<MusicPresenterList>("MusicPresenter", 1, 0, "MusicPresenterList",
                                                   QStringLiteral("ToDoList should not be created in QML"));
    qRegisterMetaType<PresenterFrame>("PresenterFrame");
    qRegisterMetaType<QSerialPort::SerialPortError>("SerialPortError");
    qRegisterMetaType<timeSlotItem>("timeSlotItem");


    QThread backendThread;
    QThread serialFrameThread;


    SerialFrameBuffer theSerialFrameBuffer;
    SerialPortal aPortal;



    timeSlotList dataList[9];
    MusicPresenterList presenterList[9];
    PresenterFrameList presenterFrameLists[9];
    theInterfaceGod theGod;

    TimeSlotListExporter theTimeSlotExporter;
    TimeSlotListImporter theTimeSlotImporter;





    theSerialFrameBuffer.moveToThread(&serialFrameThread);
    aPortal.moveToThread(&serialFrameThread);
    theTimeSlotImporter.moveToThread(&backendThread);
    theTimeSlotExporter.moveToThread(&backendThread);



    QObject::connect(&theTimeSlotExporter,&TimeSlotListExporter::SIG_reportError,&theGod,&theInterfaceGod::reportError);
    QObject::connect(&theTimeSlotExporter,&TimeSlotListExporter::SIG_reportInformation,&theGod,&theInterfaceGod::reportInformation);
    QObject::connect(&theGod,&theInterfaceGod::SIG_saveSession,&theTimeSlotExporter,&TimeSlotListExporter::saveDataToFileRequestHandler);
    QObject::connect(&theGod,&theInterfaceGod::SIG_importTimeSlotList,&theTimeSlotImporter,&TimeSlotListImporter::importFile);


    QObject::connect(&presenterFrameLists[0], &PresenterFrameList::SIG_SerialFrameBuffer_regenerateFrameList, &theSerialFrameBuffer,&SerialFrameBuffer::regenerateFrameList);


    QObject::connect(&aPortal,&SerialPortal::SIG_reportError,&theGod,&theInterfaceGod::reportError);
    QObject::connect(&aPortal,&SerialPortal::SIG_reportInformation,&theGod,&theInterfaceGod::reportInformation);
    QObject::connect(&aPortal,&SerialPortal::SIG_isConnected,&theGod,&theInterfaceGod::serialPortConnectionStatus);

    QObject::connect(&theGod, &theInterfaceGod::SIG_playFrame,&theSerialFrameBuffer, &SerialFrameBuffer::playSerialFrame);
    QObject::connect(&theGod,&theInterfaceGod::SIG_sendSerialStopFrame,&theSerialFrameBuffer,&SerialFrameBuffer::sendEmptyFrame);
    QObject::connect(&theGod,&theInterfaceGod::SIG_connectSerialPort,&aPortal,&SerialPortal::connect);
    QObject::connect(&theGod,&theInterfaceGod::SIG_disconnectSerialPort,&aPortal,&SerialPortal::disconnectSerialPort);
    QObject::connect(&theGod,&theInterfaceGod::SIG_enableSerialOutput, &theSerialFrameBuffer,&SerialFrameBuffer::setSerialEnableOutput);
    QObject::connect(&theGod,&theInterfaceGod::SIG_saveSession,&theTimeSlotExporter,&TimeSlotListExporter::saveDataToFileRequestHandler);


    QObject::connect(&serialFrameThread, &QThread::started, &aPortal,&SerialPortal::start);
    QObject::connect(&theSerialFrameBuffer,&SerialFrameBuffer::SIG_sendFrameToSerialPort,&aPortal,&SerialPortal::sendFrame);





    // CLOSE THREADS signal

    QObject::connect(&theGod,&theInterfaceGod::SIG_CloseThreads,&serialFrameThread,&QThread::quit);
    QObject::connect(&theGod,&theInterfaceGod::SIG_CloseThreads,&backendThread,&QThread::quit);
    QObject::connect(&backendThread,&QThread::finished,&theGod,&theInterfaceGod::closeApplication);



    for(int i = 0; i < 9; i++)
    {
        dataList[i].mGroup = i;
        presenterFrameLists[i].mGroup = i;
        presenterList[i].mGroup = static_cast<quint8>(i);

        QObject::connect(&dataList[i],&timeSlotList::timeSlotItemChanged,&presenterFrameLists[i],&PresenterFrameList::timeSlotChanged);
        QObject::connect(&dataList[i],&timeSlotList::timeSlotItemRemoved,&presenterFrameLists[i],&PresenterFrameList::timeSlotRemoved);

        QObject::connect(&theGod,&theInterfaceGod::SIG_regenerateFrameList,&presenterFrameLists[i],&PresenterFrameList::regenerateFrameList);
        QObject::connect(&theGod,&theInterfaceGod::SIG_playFrame, &presenterFrameLists[i],&PresenterFrameList::playFrame);
        QObject::connect(&presenterFrameLists[i],&PresenterFrameList::notifyFrameChanged,&presenterList[i],&MusicPresenterList::frameChangedHandler);
        QObject::connect(&presenterFrameLists[i],&PresenterFrameList::SIG_frameListReconstructed,&theGod,&theInterfaceGod::frameListRescontrusctedHandler);
        QObject::connect(&dataList[i],&timeSlotList::gui_timeSLotItemChanged,&theGod,&theInterfaceGod::invokeTimeSlotChanged);
        QObject::connect(&theGod,&theInterfaceGod::SIG_clearTimeSlotList,&dataList[i],&timeSlotList::clearTimeSlotList);
        QObject::connect(&presenterFrameLists[i],&PresenterFrameList::SIG_SerialFrameBuffer_notifyFrameChanged,&theSerialFrameBuffer,&SerialFrameBuffer::SerialFrameChangedHandler);

        QObject::connect(&theTimeSlotExporter,&TimeSlotListExporter::SIG_getTimeSlotList,&dataList[i],&timeSlotList::getTimeSlotList);
        QObject::connect(&dataList[i], &timeSlotList::SIG_returnTimeSlotList,&theTimeSlotExporter,&TimeSlotListExporter::timeSlotListHandler);

        QObject::connect(&theTimeSlotImporter,&TimeSlotListImporter::SIG_updateTimeSlotSlit,&dataList[i],&timeSlotList::timeSlotListImportedHandler);


        dataList[i].moveToThread(&backendThread);

    }


    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    app.setOrganizationName("Tam Duong");
    app.setOrganizationDomain("tamduongs.com");
    app.setApplicationName("ChoiNhacNuoc");

    theTimeSlotExporter.setFilePath(QCoreApplication::applicationDirPath() +"/Sessions");
    theTimeSlotImporter.setRoothPath(QCoreApplication::applicationDirPath());

    for (int i = 0; i < 9; i++)
    {
        engine.rootContext()->setContextProperty("timeSlotList_" + QString::number(i) ,&dataList[i]);
        engine.rootContext()->setContextProperty("presenterList_" + QString::number(i) ,&presenterList[i]);
    }
    engine.rootContext()->setContextProperty("theInterfaceGod", &theGod);

    engine.rootContext()->setContextProperty("appFilePath",QCoreApplication::applicationDirPath());
    // qDebug() << "AppfilePath: " + QCoreApplication::applicationDirPath();

    serialFrameThread.start(); // serialFrameThread must start before backendThread
    backendThread.start();



    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
