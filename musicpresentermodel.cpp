#include "musicpresentermodel.h"


MusicPresenterModel::MusicPresenterModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
}

MusicPresenterModel::~MusicPresenterModel()
{

}
int MusicPresenterModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();

}

QVariant MusicPresenterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const MusicPresenterItem item = mList->items().at(index.row());

    switch (role) {

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
    case LedColorRole:
        return  QVariant(item.LedColor);
    case InverterLevelRole:
        return QVariant(item.InverterLevel);
    case LEDChannelsRole:
        return QVariant(item.LedChannels);
    case ValveChannelsRole:
        return QVariant(item.ValveChannels);
      case XPosRole:
        return QVariant(item.XPos);
    case YPosRole:
        return QVariant(item.YPos);

    case OddRole:
        return QVariant(item.odd);

    }
        return QVariant();
}


bool MusicPresenterModel::setData(const QModelIndex &index, const QVariant &value,
                                  int role)
{

    if (!mList)
        return false;

    MusicPresenterItem item = mList->items().at(index.row());
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
    case LedColorRole:
        item.LedColor = value.toString();
        break;
    case InverterLevelRole:
        item.InverterLevel = static_cast<quint8>(value.toUInt());
        break;
    case LEDChannelsRole:
        item.LedChannels = static_cast<quint8>(value.toUInt());
        break;
    case ValveChannelsRole:
        item.ValveChannels = static_cast<quint8>(value.toUInt());

    case XPosRole:
        item.XPos = value.toInt();
        break;
    case YPosRole:
        item.YPos = value.toInt();
        break;
    case OddRole:
        item.odd = value.toBool();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;

}

Qt::ItemFlags MusicPresenterModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}



MusicPresenterList *MusicPresenterModel::list() const
{
    return mList;
}

void MusicPresenterModel::setList(MusicPresenterList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &MusicPresenterList::preItemAppended, this, [=]() {
            const int index = mList->items().size();

            QModelIndex theModelIndex;
            beginInsertRows(theModelIndex, index, index);
            test.append(theModelIndex);


        });
        connect(mList, &MusicPresenterList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &MusicPresenterList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &MusicPresenterList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList,&MusicPresenterList::itemChangedFromBackend,this,[=](){
            emit dataChanged(createIndex(0,0),createIndex(rowCount()-1,0), QVector<int>() );
        });
    }

    endResetModel();
}


QHash<int, QByteArray> MusicPresenterModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IDRole] = "theId";
    names[ValveOnOffRole] = "ValveOnOff";
    names[LedOnOffRole] ="LedOnOff";
    names[InverterRole] = "Inverter";
    names[InverterLevelRole] = "InverterLevel";
    names[LEDChannelsRole] = "LEDChannels";
    names[ValveChannelsRole] = "ValveChannels";
    names[LedColorRole] = "LEDColor";
    names[GroupRole] = "Group";
    names[XPosRole] = "XPos";
    names[YPosRole] = "YPos";
    names[OddRole] = "Odd";

    return names;

}

