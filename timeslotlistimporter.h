#ifndef TIMESLOTLISTIMPORTER_H
#define TIMESLOTLISTIMPORTER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <timeslotlist.h>
#include <QFile>

class TimeSlotListImporter : public QObject
{
    Q_OBJECT

    QString mRootPath;

    timeSlotItem constructTimeSlotItem(const int &group, const QJsonObject &theJsonObject);

    QString returnCorrectFileBinPath(const int &group, const QString &fileName);
    QString returnCorrectLedBinPath(const int &group, const QString &fileName);
public:
    explicit TimeSlotListImporter(QObject *parent = nullptr);
    void importFile(const QString &filePath);
    void setRoothPath(const QString &rootPath);

signals:
    void SIG_updateTimeSlotSlit(const int &group, const QVector<timeSlotItem> &list);

public slots:
};

#endif // TIMESLOTLISTIMPORTER_H
