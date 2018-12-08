#include "timeslotlist.h"

timeSlotList::timeSlotList(QObject *parent) : QObject(parent), mCurrentIndex(0), mCollisionSide(false), mGroup(0)
{

}

timeSlotList::~timeSlotList()
{

}


QVector<timeSlotItem> timeSlotList::items() const
{
    return mItems;
}


bool timeSlotList::setItemAt(int index, const timeSlotItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;

    emit timeSlotItemChanged(item);
    emit gui_timeSLotItemChanged();
    return true;
}

void timeSlotList::copyItem(const int &id, const int &fromMs)
{
    emit preItemAppended();

    timeSlotItem item;
    for (int i = 0; i < mItems.size(); i++)
    {
        if(mItems.at(i).id == id)
        {
            item = mItems.at(i);
            break;
        }

    }

    item.id  = mCurrentIndex;

    int duration = item.toMs - item.fromMs;
    item.fromMs =fromMs;
    item.toMs = fromMs + duration;

    mCurrentIndex++;
    mItems.append(item);

    emit postItemAppended();
}

void timeSlotList::appendItem(const quint8 &group, const int &fromMs, const int &toMs)
{
    emit preItemAppended();
    timeSlotItem item;

    item.id = mCurrentIndex;
    item.fromMs = fromMs;
    item.toMs = toMs;
    item.ValveOnOff = false;
    item.LedOnOff = true;
    item.LedMode = 0;
    item.InverterLevel = 0;
    item.Inverter = false;
    item.ValveMode = 1;
    item.ValveSpeed = 0;
    item.LedValuesList = "grey";
    item.LedSync = false;
    switch(group)
    {
    case 0:
        item.Inverter = true;
        item.LedChannels = 1;
        item.ValveChannels = 1;

        break;
    case 1:
        item.LedChannels = 1;
        item.ValveChannels = 8;
        break;
    case 2:
        item.LedChannels = 1;
        item.ValveChannels = 16;
        break;
    case 3:
        item.LedChannels = 1;
        item.Inverter = true;
        item.ValveChannels = 1;
        break;
    case 4:
        item.LedChannels = 1;
        item.ValveChannels = 1;
        break;
    case 5:
        item.LedChannels = 2;
        item.Inverter = true;
        item.ValveChannels = 2;
        break;
    case 6:
        item.LedChannels = 2;
        item.ValveChannels = 2;
        break;
    case 7:
        item.LedChannels = 8;
        item.ValveChannels = 8;
        break;
    case 8:
        item.LedChannels = 2;
        item.ValveChannels = 2;
        break;

    }


    mItems.append(timeSlotCollisionAdjust(item));
    mCurrentIndex++;

    emit postItemAppended();
    //    emit timeSlotItemChanged(item);
}

void timeSlotList::removeItems(const int &id)
{
    for (int i = 0; i < mItems.size(); ) {
        if (mItems.at(i).id == id) {
            emit preItemRemoved(i);
            emit timeSlotItemRemoved(mItems.at(i));
            mItems.removeAt(i);

            emit postItemRemoved();


            return;
        } else {
            ++i;
        }
    }
}

timeSlotItem timeSlotList::getTimeSlotItem(const int &id)
{
    for (int i = 0; i < mItems.size(); i++)
    {
        if(mItems.at(i).id == id)
        {
            return mItems.at(i);
        }
    }

    return timeSlotItem();
}

bool timeSlotList::getCollisionSide()
{
    return mCollisionSide;
}

int timeSlotList::count()
{
    return mItems.size();
}
int timeSlotList::lastIndex() const
{
    return mCurrentIndex - 1;
}

void timeSlotList::getTimeSlotList()
{
    emit SIG_returnTimeSlotList(mGroup,mItems);
}

int timeSlotList::timeSlotCollisionCheck(const int &id)
{

    timeSlotItem theTimeSlot = getTimeSlotItem(id);

    for(int i = 0; i < mItems.count(); i++ )
    {
        if(mItems.at(i).id != theTimeSlot.id)
        {
            if(theTimeSlot.fromMs  >= mItems.at(i).fromMs && theTimeSlot.fromMs  <= mItems.at(i).toMs)
            {
                mCollisionSide = false;
                return mItems.at(i).toMs;
            }
            else if(theTimeSlot.toMs  >= mItems.at(i).fromMs && theTimeSlot.toMs  <= mItems.at(i).toMs)
            {
                mCollisionSide = true;
                return mItems.at(i).fromMs - (theTimeSlot.toMs  - theTimeSlot.fromMs ) ;
            }

        }

    }
    return 0;
    //    return false;
}

timeSlotItem timeSlotList::timeSlotCollisionAdjust(const timeSlotItem &item)
{
    timeSlotItem tmpItem = item;
    bool fromChecked =false, toChecked = false;

    for(int i = 0; i < mItems.count(); i++ )
    {
        if(mItems.at(i).id != tmpItem.id)
        {
            if(tmpItem.fromMs  >= mItems.at(i).fromMs && tmpItem.fromMs  <= mItems.at(i).toMs && !fromChecked)
            {
                tmpItem.fromMs = mItems.at(i).toMs+1;

                fromChecked = true;

            }
            else if(tmpItem.toMs  >= mItems.at(i).fromMs && tmpItem.toMs  <= mItems.at(i).toMs && !toChecked)
            {

                tmpItem.toMs = mItems.at(i).fromMs -1;
                toChecked = true;

            }

            if(fromChecked && toChecked)
            {
                return tmpItem;
            }

        }

    }



    return  tmpItem;
}


void timeSlotList::timeSlotListImportedHandler(const int &group, const QVector<timeSlotItem> &list)
{

    if(mGroup != group)
    {
        return;
    }


    mItems.clear();
    mCurrentIndex = 0;


    for(int i = 0; i < list.size(); i++)
    {
        emit preItemAppended();

        mItems.append(list.at(i));


        if(list.at(i).id >= mCurrentIndex)
        {
            mCurrentIndex = list.at(i).id;
        }


        emit postItemAppended();

    }

    mCurrentIndex++;

    emit SIG_NotifyListChanged();

}

void timeSlotList::clearTimeSlotList()
{
    mItems.clear();
    mCurrentIndex = 0;

    emit SIG_NotifyListChanged();
}

void timeSlotList::updateAllTimeSlots()
{
    for(int i = 0; i < mItems.size(); i++)
    {
        emit timeSlotItemChanged(mItems.at(i));
    }
}
