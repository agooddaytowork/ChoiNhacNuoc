#include "timeslotlistexporter.h"

TimeSlotListExporter::TimeSlotListExporter(QObject *parent): QObject(parent), mFilePath(""), mFileName(""), mHandlerCnt(0)
{

}

void TimeSlotListExporter::setFilePath(const QString &filePath)
{
    mFilePath = filePath;
}


void TimeSlotListExporter::timeSlotListHandler(const int &group, const QVector<timeSlotItem> &list)
{

    qDebug() << "timeSlotListHandler--- group : " + QString::number(group);
    QJsonObject thePackage;

    thePackage.insert("group", group);
    QJsonArray data;

    for(int i = 0; i < list.size(); i++)
    {
        QJsonObject item;

        const timeSlotItem theItem = list.at(i);

        item.insert( "id", theItem.id);
        item.insert("ValveOnOff",theItem.ValveOnOff);
        item.insert("Inverter", theItem.Inverter);
        item.insert("LedOnOff",theItem.LedOnOff);
        item.insert("FromMs", theItem.fromMs);
        item.insert("ToMs", theItem.toMs);
        item.insert("LedMode", theItem.LedMode);
        item.insert("InverterLevel", theItem.InverterLevel);
        item.insert("FileBinPath", theItem.fileBinPath);
        item.insert("LEDValuesList", theItem.LedValuesList);
        item.insert("LEDChannels", theItem.LedChannels);
        item.insert("ValveChannels", theItem.ValveChannels);
        item.insert("ValveMode", theItem.ValveMode);
        item.insert("ValveSpeed", theItem.ValveSpeed);
        item.insert("ValveModeName", theItem.ValveModeName);
        item.insert("LedModeName", theItem.LedModeName);
        item.insert("LedSpeed", theItem.LedSpeed);
        item.insert("LedSync", theItem.LedSync);
        item.insert("ValveForceRepeat", theItem.ValveForceRepeat);
        item.insert("ValveForceRepeatTimes", theItem.ValveForceRepeatTimes);
        item.insert("LedBinPath",theItem.LedBinPath);
        item.insert("UseLedBuiltInEffects", theItem.UseLedBuiltInEffects);
        item.insert("LedForceRepeat",theItem.LedForceRepeat);
        item.insert("LedForceRepeatTimes",theItem.LedForceRepeatTimes);

        data.append(item);

    }

    thePackage.insert("data", data);

    mJsonData.append(thePackage);

    mHandlerCnt++;

    if(mHandlerCnt == 9)
    {
        // save file to JSON

        saveDataToFile();
    }
}

void TimeSlotListExporter::setFileName(const QString &name)
{
    qDebug() << "setFileName--- : " + name;
    mFileName = name;
}



bool TimeSlotListExporter::saveDataToFile()
{
    qDebug() << "saveDataToFile--- : " + mFilePath+"/"+mFileName;
    QFile file(mFilePath+"/"+mFileName+".bin");

    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "file opened";
        mHandlerCnt = 0;

        QJsonArray theArray;

        for(int i =0 ; i < mJsonData.size(); i++)
        {
            theArray.insert(i,mJsonData.at(i));
        }

        QJsonDocument theDocument(theArray);

        file.write(theDocument.toJson());

         mJsonData.clear();
        return true;
    }
      qDebug() << "file is not opened";

    return false;
}


void TimeSlotListExporter::saveDataToFileRequestHandler(const QString &fileName)
{
    qDebug() << "saveDataToFileRequestHandler: " +fileName;
    setFileName(fileName);
    emit SIG_getTimeSlotList();
}
