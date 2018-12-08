#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <QString>
#include <QMap>
#include <QByteArray>

class timeSlot
{
    int mID;
    bool mValveONOFF;
    bool mLEDONOFF;
    bool mInverter;
    int mFromMs;
    int mToMs;
    int mLEDMode;
    quint8 mInverterLevel;
    QString mFileBinPath;
    QMap<int,QByteArray> mLEDValuesList; // <position in time Domain, LED Value>

public:
    timeSlot();
};

#endif // TIMESLOT_H
