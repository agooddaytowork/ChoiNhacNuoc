#ifndef TIMESLOTLISTEXPORTER_H
#define TIMESLOTLISTEXPORTER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

#include "timeslotlist.h"



class TimeSlotListExporter: public QObject
{

    Q_OBJECT

    QString mFilePath;
    QString mFileName;
    QList<QJsonObject> mJsonData;

    int mHandlerCnt;

public:
    TimeSlotListExporter(QObject *parent = nullptr);

    void timeSlotListHandler(const int &group, const QVector<timeSlotItem> &list);
    void setFilePath(const QString &filePath);
    void setFileName(const QString &name);
    bool saveDataToFile();
    void saveDataToFileRequestHandler(const QString &fileName);

signals:

    void SIG_getTimeSlotList();
    void SIG_reportError(const QString &title, const QString &content);
    void SIG_reportInformation(const QString &title, const QString &content);
};

#endif // TIMESLOTLISTEXPORTER_H

