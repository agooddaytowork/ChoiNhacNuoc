#ifndef TIMESLOTMODEL_H
#define TIMESLOTMODEL_H

#include <QAbstractListModel>
#include "timeslotlist.h"
#include <QModelIndex>

class timeSlotModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(timeSlotList *list READ list WRITE setList NOTIFY listChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)

    QModelIndex mModelIndex;
public:
    explicit timeSlotModel(QObject *parent = nullptr);

    enum {
        IDRole = Qt::UserRole,
        GroupRole,
        ValveOnOffRole,
        LedOnOffRole,
        InverterRole,
        FromMsRole,
        ToMsRole,
        InverterLevelRole,
        FileBinPathRole,
        LEDValuesListRole,
        LEDChannelsRole,
        ValveChannelsRole,
        ValveModeRole,
        ValveSpeedRole,
        ValveModeNameRole,
        LedSpeedRole,
        LedModeNameRole,
        LedModeRole,
        LedSyncRole,
        ValveForceRepeatRole,
        ValveForceRepeatTimesRole,
        LedBinPath,
        LedBuiltIntEffectRole,
        LedForceRepeatRole,
        LedForceRepeatTimesRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

//    Q_INVOKABLE timeSlotItem at(const int &index);

     QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:

     void setIndexToList(const QModelIndex &index, const int &row);
     bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    Q_INVOKABLE QVariant getDataPerIndex(const int &index, const QByteArray &RoleString);

    Q_INVOKABLE bool    setDataPerIndex(const int &index, const QByteArray &RoleString, const QVariant &value);
    virtual QHash<int, QByteArray> roleNames() const override;

    timeSlotList *list() const;
    void setList(timeSlotList *list);

    int size() const;
    void setSize(int size);


signals:

    void sizeChanged();
    void listChanged();
    void gui_timeSlotItemChanged();

private:
    timeSlotItem getTimeSlotItemPerId(const int &id);
    int getIndexPerId(const int &id) const;

    timeSlotList *mList;
    int mSize;
};

#endif // TIMESLOTMODEL_H
