#ifndef LED_BINEFFECTS_H
#define LED_BINEFFECTS_H

#include <QFile>
#include <QMap>
#include <QList>
#include <QColor>

class LED_BinEffects
{
    bool mEffectValid;
    QString mFilePath;
    QByteArray mEffectBytes;

    QList<QList<QColor>> rawColorMatrix;
    QList<QList<QColor>> forcedColorMatrix;
    QList<QList<QColor>> speedColorMatrix;

    int mSpeed;
    bool mForceRepeat;
    bool mForceRepeatJustChanged;
    int mRepeatTime;
    int mFrameNo;
    int mLedNo;
    bool mFilePathJustChanged;
public:
    LED_BinEffects();
    bool setNewPath( QString filePath, const int &ledNo);
    bool isEffectValid();
    bool setSpeed(const int &speed);
    bool setForceRepeat(const bool &forcedRepeat, const int &repeatTime);
    QColor getData(const int &index, const int &ledOrder);

};

#endif // LED_BINEFFECTS_H
