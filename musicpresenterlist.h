#ifndef MUSICPRESENTERLIST_H
#define MUSICPRESENTERLIST_H

#include <QObject>
#include <QVector>
#include "presenterframelist.h"


struct MusicPresenterItem{
    int id;
    quint8 group;
    bool ValveOnOff;
    bool LedOnOff;
    bool Inverter;
    QString LedColor;
    quint8 InverterLevel;
    quint8 LedChannels;
    quint8 ValveChannels;
    int XPos;
    int YPos;
    bool odd;

};


class MusicPresenterList: public QObject
{
    Q_OBJECT

    QVector<MusicPresenterItem> mItems;
    int mCurrentIndex;


public:
    explicit MusicPresenterList(QObject *parent = nullptr);
    ~MusicPresenterList();
    quint8 mGroup;

    QVector<MusicPresenterItem> items() const;
    bool setItemAt(int index, const MusicPresenterItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();
    void itemChangedFromBackend();

public slots:

    void appendItem(const quint8 &group, int xPos, int yPos);
    void appenItemGroup6(bool odd, int xPos, int yPos);
    void removeItems(const int &id);
    void clear();
    void frameChangedHandler(const PresenterFrame &frame);
};

#endif // MUSICPRESENTERLIST_H
