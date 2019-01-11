#include "timeslotlistimporter.h"
#include <QDebug>
#include <QUrl>

TimeSlotListImporter::TimeSlotListImporter(QObject *parent) : QObject(parent)
{

}

timeSlotItem TimeSlotListImporter::constructTimeSlotItem(const int &group, const QJsonObject &theJsonObject)
{


    timeSlotItem theItem;

    theItem.id = theJsonObject.value("id").toInt(0);
    theItem.ValveOnOff = theJsonObject.value("ValveOnOff").toBool(false);
    theItem.Inverter = theJsonObject.value("Inverter").toBool(false);
    theItem.LedOnOff = theJsonObject.value("LedOnOff").toBool(true);
    theItem.fromMs = theJsonObject.value("FromMs").toInt(0);
    theItem.toMs = theJsonObject.value("ToMs").toInt(0);
    theItem.LedMode = static_cast<quint8>(theJsonObject.value("LedMode").toInt(0));
    theItem.InverterLevel = static_cast<quint8>(theJsonObject.value("InverterLevel").toInt(0)) ;
    theItem.fileBinPath = returnCorrectFileBinPath(group, theJsonObject.value("ValveModeName").toString(""));
    theItem.LedValuesList = theJsonObject.value("LEDValuesList").toString("");
    theItem.LedChannels = static_cast<quint8>(theJsonObject.value("LEDChannels").toInt(0));
    theItem.ValveChannels = static_cast<quint8>(theJsonObject.value("ValveChannels").toInt(0));
    theItem.ValveMode = static_cast<quint8>(theJsonObject.value("ValveMode").toInt(0));
    theItem.ValveSpeed = theJsonObject.value("ValveSpeed").toInt(0);
    theItem.ValveModeName = theJsonObject.value("ValveModeName").toString();
    theItem.LedModeName = theJsonObject.value("LedModeName").toString();
    theItem.LedSpeed = theJsonObject.value("LedSpeed").toInt();
    theItem.LedSync = theJsonObject.value("LedSync").toBool();
    theItem.ValveForceRepeat = theJsonObject.value("ValveForceRepeat").toBool();
    theItem.ValveForceRepeatTimes = theJsonObject.value("ValveForceRepeatTimes").toInt();
    theItem.LedBinPath = returnCorrectLedBinPath(group,theJsonObject.value("LedModeName").toString(""));
    theItem.UseLedBuiltInEffects = theJsonObject.value("UseLedBuiltInEffects").toBool();
    theItem.LedForceRepeat = theJsonObject.value("LedForceRepeat").toBool();
    theItem.LedForceRepeatTimes = theJsonObject.value("LedForceRepeatTimes").toInt();
    theItem.ledSyncDelay = theJsonObject.value("LedSyncDelay").toInt();


    return theItem;
}


QString TimeSlotListImporter::returnCorrectFileBinPath(const int &group, const QString &fileName)
{
    QString groupFolderPath = "/ValveEffects/";

    switch(group)
    {
    case 0:
        groupFolderPath  += "Kieu1/";
        break;

    case 1:
        groupFolderPath +="Kieu2/";
        break;
    case 2:
        groupFolderPath +="Kieu3/";
        break;
    case 3:
        groupFolderPath +="Kieu4/";
        break;
    case 4:
        groupFolderPath +="Kieu5/";
        break;
    case 5:
        groupFolderPath +="Kieu6/";
        break;
    case 6:
        groupFolderPath +="Kieu7/";
        break;
    case 7:
        groupFolderPath +="Kieu8/";
        break;
    case 8:
        groupFolderPath +="Kieu9/";
        break;

    }

    return mRootPath + groupFolderPath + fileName;
}

QString TimeSlotListImporter::returnCorrectLedBinPath(const int &group, const QString &fileName)
{
    QString groupFolderPath = "/LedEffects/";

    switch(group)
    {
    case 0:
        groupFolderPath  += "Kieu1/";
        break;

    case 1:
        groupFolderPath +="Kieu2/";
        break;
    case 2:
        groupFolderPath +="Kieu3/";
        break;
    case 3:
        groupFolderPath +="Kieu4/";
        break;
    case 4:
        groupFolderPath +="Kieu5/";
        break;
    case 5:
        groupFolderPath +="Kieu6/";
        break;
    case 6:
        groupFolderPath +="Kieu7/";
        break;
    case 7:
        groupFolderPath +="Kieu8/";
        break;
    case 8:
        groupFolderPath +="Kieu9/";
        break;

    }

    return mRootPath + groupFolderPath + fileName;
}

void TimeSlotListImporter::importFile(const QString &filePath)
{


//    // qDebug() << "TimeSlotListImporter::importFile :" +QUrl(filePath).toLocalFile();

    QFile file(QUrl(filePath).toLocalFile());

    if(file.open(QIODevice::ReadOnly ))
    {
//        qDebug()<< "file is oPen";
        QByteArray data = file.readAll();



        QJsonDocument theDocument = QJsonDocument::fromJson(data);


        if(!theDocument.isNull())
        {
//            qDebug()<< "Document is not null";

            QJsonArray groupsArray = theDocument.array();

            for(int i = 0; i < groupsArray.count(); i++)
            {

                QJsonObject theGroup = groupsArray.at(i).toObject();
                QJsonArray timeSlotsArray = theGroup.value("data").toArray();
                QVector<timeSlotItem> timeSlotList;

                for(int ii = 0; ii < timeSlotsArray.count(); ii++)
                {
                    timeSlotList.append(constructTimeSlotItem(theGroup.value("group").toInt(), timeSlotsArray.at(ii).toObject()));
                }

//                // qDebug() << "Emit shits";

                emit SIG_updateTimeSlotSlit(theGroup.value("group").toInt(), timeSlotList);

            }


        }


    }
    else
    {
        // qDebug() << file.errorString();
//        // qDebug() << "file is not open";
    }

}

void TimeSlotListImporter::setRoothPath(const QString &rootPath)
{
    mRootPath = rootPath;
}
