#ifndef TIMESLOTLIST_H
#define TIMESLOTLIST_H

#include <QObject>
#include <QVector>
#include <QModelIndex>

struct timeSlotItem{
    //        Q_GADGET
    int id;
    int fromMs;
    int toMs;
    quint8 group;
    bool ValveOnOff = false;
    bool LedOnOff = true;
    bool Inverter = false;
    bool LedSync = false;
    quint8 LedMode = 0;
    quint8 InverterLevel = 0;
    QString fileBinPath ="";
    QString LedValuesList ="";
    quint8 LedChannels = 0;
    quint8 ValveChannels =0;
    quint8 ValveMode =0;
    QString ValveModeName="";
    QString LedModeName="";
    int ValveSpeed=0;
    int LedSpeed=0;
    QModelIndex modelIndex;
    bool ValveForceRepeat = false;
    int ValveForceRepeatTimes = 0;
    QString LedBinPath;
    bool UseLedBuiltInEffects = false;
    bool LedForceRepeat = false;
    int  LedForceRepeatTimes = 0;
    bool valid = true;
    int ledSyncDelay = 0;
};


class timeSlotList : public QObject
{
    Q_OBJECT

    QVector<timeSlotItem> mItems;
    int mCurrentIndex;
    bool mCollisionSide;

    timeSlotItem getTimeSlotItem(const int &id);

    timeSlotItem timeSlotCollisionAdjust(const timeSlotItem &item);

public:
    int mGroup;
    explicit timeSlotList(QObject *parent = nullptr);
    QVector<timeSlotItem> items() const;
    bool setItemAt(int index, const timeSlotItem &item);
    Q_INVOKABLE int timeSlotCollisionCheck(const int &id);
    Q_INVOKABLE bool getCollisionSide();
    Q_INVOKABLE int count();
    Q_INVOKABLE int lastIndex() const;
    Q_INVOKABLE void updateAllTimeSlots();

    void getTimeSlotList();


    ~timeSlotList();

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();
    void timeSlotItemChanged(const timeSlotItem &item);
    void timeSlotItemRemoved(const timeSlotItem &item);
    void gui_timeSLotItemChanged();

    void SIG_returnTimeSlotList(const int &group, const QVector<timeSlotItem> &list );

    void SIG_NotifyListChanged();

    void SIG_reportError(const QString &title, const QString &content);

public slots:

    void appendItem(const int &group, const int &fromMs, const int &toMs);
    void copyItem(const int &id, const int &fromMs);
    void removeItems(const int &id);
    void timeSlotListImportedHandler(const int &group, const QVector<timeSlotItem> &list);
    void clearTimeSlotList();

};


#endif // TIMESLOTLIST_H
