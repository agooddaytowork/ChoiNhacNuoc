#include "timeslotmodel.h"
#include <QDebug>

timeSlotModel::timeSlotModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr), mSize(0)
{
}

int timeSlotModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;
    return mList->items().size();
}


timeSlotItem timeSlotModel::getTimeSlotItemPerId(const int &id)
{
    timeSlotItem item;



    for(int i =0; i < mList->count(); i++)
    {
        //        // qDebug() << "current ID in list: " + QString::number(mList->items().at(i).id) ;
        if(mList->items().at(i).id == id)
        {
            return mList->items().at(i);
        }
    }

    item.valid = false;
   // qDebug() << "Time Slot Model timeSlot not found in list, group: " + QString::number(mList->mGroup);
    return item;
}


int timeSlotModel::getIndexPerId(const int &id) const
{
    for(int i =0; i < mList->count(); i++)
    {
        if(mList->items().at(i).id == id)
        {
            return i;
        }
    }

    return -1;
}
QVariant timeSlotModel::getDataPerIndex(const int &index, const QByteArray &RoleString)
{
    if(/*index-1  > mList->count() ||*/ !mList || mList->count() ==  0)
    {
        return QVariant();
    }

    int role = timeSlotModel::roleNames().key(RoleString);


    const timeSlotItem item = getTimeSlotItemPerId(index);

    if(item.valid)
    {
        switch(role)
        {
        case IDRole:
            return QVariant(item.id);
        case GroupRole:
            return QVariant(item.group);
        case ValveOnOffRole:
            return QVariant(item.ValveOnOff);
        case LedOnOffRole:
            return QVariant(item.LedOnOff);
        case InverterRole:
            return QVariant(item.Inverter);
        case FromMsRole:
            return QVariant(item.fromMs);
        case ToMsRole:
            return QVariant(item.toMs);

        case InverterLevelRole:
            return QVariant(item.InverterLevel);
        case FileBinPathRole:
            return QVariant(item.fileBinPath);
        case LEDValuesListRole:
            return QVariant(item.LedValuesList);
        case LEDChannelsRole:
            return QVariant(item.LedChannels);
        case ValveChannelsRole:
            return QVariant(item.ValveChannels);
        case ValveModeRole:
            return QVariant(item.ValveMode);
        case ValveSpeedRole:
            return QVariant(item.ValveSpeed);
        case LedModeRole:
            return QVariant(item.LedMode);
        case ValveModeNameRole:
            return QVariant(item.ValveModeName);
        case LedModeNameRole:
            return QVariant(item.LedModeName);
        case LedSpeedRole:
            return QVariant(item.LedSpeed);
        case LedSyncRole:
            return  QVariant(item.LedSync);
        case ValveForceRepeatRole:
            return QVariant(item.ValveForceRepeat);
        case ValveForceRepeatTimesRole:
            return QVariant(item.ValveForceRepeatTimes);
        case LedBinPath:
            return QVariant(item.LedBinPath);
        case LedBuiltIntEffectRole:
            return QVariant(item.UseLedBuiltInEffects);
        case LedForceRepeatRole:
            return QVariant(item.LedForceRepeat);
        case LedForceRepeatTimesRole:
            return QVariant(item.LedForceRepeatTimes);
        case LedSyncDelayRole:
            return QVariant(item.ledSyncDelay);



        }
    }


    return QVariant();
}


void timeSlotModel::setIndexToList(const QModelIndex &index, const int &row)
{
    timeSlotItem item = mList->items().at(row);

    item.modelIndex = index;

    mList->setItemAt(row,item);
}


QVariant timeSlotModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();




    const timeSlotItem item = mList->items().at(index.row());


    switch(role)
    {
    case IDRole:
        return QVariant(item.id);
    case GroupRole:
        return QVariant(item.group);
    case ValveOnOffRole:
        return QVariant(item.ValveOnOff);
    case LedOnOffRole:
        return QVariant(item.LedOnOff);
    case InverterRole:
        return QVariant(item.Inverter);
    case FromMsRole:
        return QVariant(item.fromMs);
    case ToMsRole:
        return QVariant(item.toMs);
    case LedModeRole:
        return QVariant(item.LedMode);
    case InverterLevelRole:
        return QVariant(item.InverterLevel);
    case FileBinPathRole:
        return QVariant(item.fileBinPath);
    case LEDValuesListRole:
        return QVariant(item.LedValuesList);
    case LEDChannelsRole:
        return QVariant(item.LedChannels);
    case ValveChannelsRole:
        return QVariant(item.ValveChannels);

    case ValveModeRole:
        return QVariant(item.ValveMode);

    case ValveSpeedRole:
        return QVariant(item.ValveSpeed);

    case ValveModeNameRole:
        return QVariant(item.ValveModeName);
    case LedModeNameRole:
        return  QVariant(item.LedModeName);
    case LedSpeedRole:
        return QVariant(item.LedSpeed);
    case LedSyncRole:
        return  QVariant(item.LedSync);
    case ValveForceRepeatRole:
        return QVariant(item.ValveForceRepeat);
    case ValveForceRepeatTimesRole:
        return QVariant(item.ValveForceRepeatTimes);
    case LedBinPath:
        return QVariant(item.LedBinPath);
    case LedBuiltIntEffectRole:
        return QVariant(item.UseLedBuiltInEffects);
    case LedForceRepeatRole:
        return QVariant(item.LedForceRepeat);
    case LedForceRepeatTimesRole:
        return QVariant(item.LedForceRepeatTimes);
    case LedSyncDelayRole:
        return QVariant(item.ledSyncDelay);



    }

    return QVariant();
}

bool timeSlotModel::setDataPerIndex(const int &index, const QByteArray &RoleString, const QVariant &value)
{
    if(/*index -1 > mList->count() ||*/ !mList)
    {
        return false;
    }

    int role = timeSlotModel::roleNames().key(RoleString);
    timeSlotItem item = getTimeSlotItemPerId(index);

    if(item.valid)
    {
        switch (role) {
        case IDRole:
            item.id = static_cast<int>(value.toUInt());
            break;
        case GroupRole:
            item.group = static_cast<quint8>(value.toUInt());
            break;
        case ValveOnOffRole:
            item.ValveOnOff = value.toBool();
            break;
        case LedOnOffRole:
            item.LedOnOff = value.toBool();
            break;
        case InverterRole:
            item.Inverter = value.toBool();
            break;
        case FromMsRole:
            item.fromMs = static_cast<int>(value.toUInt());
            break;
        case ToMsRole:
            item.toMs = static_cast<int>(value.toUInt());
        case LedModeRole:
            item.LedMode = static_cast<quint8>(value.toUInt());
            break;
        case InverterLevelRole:
            item.InverterLevel = static_cast<quint8>(value.toUInt());
            break;
        case FileBinPathRole:
            item.fileBinPath = value.toString();
            break;
        case LEDValuesListRole:
            item.LedValuesList = value.toString();
            break;
        case LEDChannelsRole:
            item.LedChannels = static_cast<quint8>(value.toUInt());
            break;
        case ValveChannelsRole:
            item.ValveChannels = static_cast<quint8>(value.toUInt());
            break;

        case ValveModeRole:
            item.ValveMode = static_cast<quint8>(value.toUInt());
            break;

        case ValveSpeedRole:
            item.ValveSpeed = value.toInt();
            break;

        case ValveModeNameRole:
            item.ValveModeName = value.toString();
            break;
        case LedModeNameRole:
            item.LedModeName = value.toString();
            break;
        case LedSpeedRole:
            item.LedSpeed = value.toInt();
            break;
        case LedSyncRole:
            item.LedSync = value.toBool();
            break;
        case ValveForceRepeatRole:
            item.ValveForceRepeat = value.toBool();
            break;
        case ValveForceRepeatTimesRole:
            item.ValveForceRepeatTimes = value.toInt();
            break;
        case LedBinPath:
            item.LedBinPath = value.toString();
            break;
        case LedBuiltIntEffectRole:
            item.UseLedBuiltInEffects = value.toBool();
            break;
        case LedForceRepeatRole:
            item.LedForceRepeat = value.toBool();
            break;
        case LedForceRepeatTimesRole:
            item.LedForceRepeatTimes = value.toInt();
            break;
        case LedSyncDelayRole:
            item.ledSyncDelay = value.toInt();
            break;
        }
    }


    if (mList->setItemAt(getIndexPerId(index), item)) {


        //         emit dataChanged(createIndex(index,0), createIndex(index,0), QVector<int>() << role);
        emit gui_timeSlotItemChanged();

        return true;
    }
    return false;

}

bool timeSlotModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (!mList)
        return false;

    timeSlotItem item = mList->items().at(index.row());

    if(item.modelIndex != index)
    {
        item.modelIndex = index;
    }

    switch (role) {
    case IDRole:
        item.id = static_cast<int>(value.toUInt());
        break;
    case GroupRole:
        item.group = static_cast<quint8>(value.toUInt());
        break;
    case ValveOnOffRole:
        item.ValveOnOff = value.toBool();
        break;
    case LedOnOffRole:
        item.LedOnOff = value.toBool();
        break;
    case InverterRole:
        item.Inverter = value.toBool();
        break;
    case FromMsRole:
        item.fromMs = static_cast<int>(value.toUInt());
        break;
    case ToMsRole:
        item.toMs = static_cast<int>(value.toUInt());
    case LedModeRole:
        item.LedMode = static_cast<quint8>(value.toUInt());
        break;
    case InverterLevelRole:
        item.InverterLevel = static_cast<quint8>(value.toUInt());
        break;
    case FileBinPathRole:
        item.fileBinPath = value.toString();
        break;
    case LEDValuesListRole:
        item.LedValuesList = value.toString();
        break;
    case LEDChannelsRole:
        item.LedChannels = static_cast<quint8>(value.toUInt());
        break;
    case ValveChannelsRole:
        item.ValveChannels = static_cast<quint8>(value.toUInt());

    case ValveModeRole:
        item.ValveMode = static_cast<quint8>(value.toUInt());

    case ValveSpeedRole:
        item.ValveSpeed = value.toInt();
    case ValveModeNameRole:
        item.ValveModeName = value.toString();
    case LedModeNameRole:
        item.LedModeName = value.toString();
    case LedSpeedRole:
        item.LedSpeed = value.toInt();
    case LedSyncRole:
        item.LedSync = value.toBool();
        break;
    case ValveForceRepeatRole:
        item.ValveForceRepeat = value.toBool();
        break;
    case ValveForceRepeatTimesRole:
        item.ValveForceRepeatTimes = value.toInt();
        break;
    case LedBinPath:
        item.LedBinPath = value.toString();
        break;
    case LedBuiltIntEffectRole:
        item.UseLedBuiltInEffects = value.toBool();
        break;
    case LedForceRepeatRole:
        item.LedForceRepeat = value.toBool();
        break;
    case LedForceRepeatTimesRole:
        item.LedForceRepeatTimes = value.toInt();
        break;
    case LedSyncDelayRole:
        item.ledSyncDelay = value.toInt();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        //        // qDebug() << "setData";
        return true;
    }
    return false;
}

Qt::ItemFlags timeSlotModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> timeSlotModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IDRole] = "theId";
    names[ValveOnOffRole] = "ValveOnOff";
    names[LedOnOffRole] ="LedOnOff";
    names[InverterRole] = "Inverter";
    names[FromMsRole] = "FromMs";
    names[ToMsRole] = "ToMs";
    names[LedModeRole] = "LedModeHihi";
    names[InverterLevelRole] = "InverterLevel";
    names[FileBinPathRole] = "FileBinPath";
    names[LEDValuesListRole] = "LEDValuesList";
    names[LEDChannelsRole] = "LEDChannels";
    names[ValveChannelsRole] = "ValveChannels";
    names[ValveModeRole] = "ValveMode";
    names[ValveSpeedRole] = "ValveSpeed";
    names[ValveModeNameRole] = "ValveModeName";
    names[LedModeNameRole] = "LedModeName";
    names[LedSpeedRole] = "LedSpeed";
    names[LedSyncRole] = "LedSync";
    names[ValveForceRepeatRole] = "ValveForceRepeat";
    names[ValveForceRepeatTimesRole] = "ValveForceRepeatTimes";
    names[LedBinPath] = "LedBinPath";
    names[LedBuiltIntEffectRole] = "UseLedBuiltInEffects";
    names[LedForceRepeatRole] = "LedForceRepeat";
    names[LedForceRepeatTimesRole] = "LedForceRepeatTimes";
    names[LedSyncDelayRole] = "LedSyncDelay";


    return names;

}


timeSlotList *timeSlotModel::list() const
{
    return mList;
}

void timeSlotModel::setList(timeSlotList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &timeSlotList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &timeSlotList::postItemAppended, this, [=]() {

            this->setSize(mList->count());
            endInsertRows();

        });

        connect(mList, &timeSlotList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);

        });
        connect(mList, &timeSlotList::postItemRemoved, this, [=]() {

            this->setSize(mList->count());
            endRemoveRows();
        });

        connect(mList,&timeSlotList::SIG_NotifyListChanged,this,[=](){

            //            // qDebug() << "list change ne dmmm";
            //             emit dataChanged(createIndex(0,0), createIndex(rowCount()-1,0), QVector<int>());

            emit this->listChanged();
        });
    }

    endResetModel();
}

int timeSlotModel::size() const
{
    return mSize;
}

void timeSlotModel::setSize( int size)
{
    if(mSize != size)
    {
        mSize = size;
        sizeChanged();
    }

}

//timeSlotItem timeSlotModel::at(const int &index)
//{
//    return mList->items().at(index);
//}
