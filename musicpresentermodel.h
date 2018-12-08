#ifndef MUSICPRESENTERMODEL_H
#define MUSICPRESENTERMODEL_H

#include <QAbstractListModel>
#include "musicpresenterlist.h"
#include <QVector>
#include <QModelIndex>

class MusicPresenterModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(MusicPresenterList *list READ list WRITE setList)
    QVector<QModelIndex> test;
public:
     ~MusicPresenterModel() override;
    explicit MusicPresenterModel(QObject *parent = nullptr);

    enum{
        IDRole = Qt::UserRole,
        GroupRole,
        ValveOnOffRole,
        LedOnOffRole,
        InverterRole,
        LedColorRole,
        InverterLevelRole,
        LEDChannelsRole,
        ValveChannelsRole,
        XPosRole,
        YPosRole,
        OddRole

    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;


    MusicPresenterList *list() const;
    void setList(MusicPresenterList *list);



private:
     MusicPresenterList *mList;

};

#endif // MUSICPRESENTERMODEL_H
