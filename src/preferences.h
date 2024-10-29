#ifndef Preferences_H
#define Preferences_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFileDialog>

#define byte unsigned char


class Preferences : public QObject
{
    Q_OBJECT
public:

    Preferences(Preferences const&) = delete;
    Preferences& operator=(Preferences const&) = delete;

    Preferences();
    ~Preferences();

    static Preferences *instance;

    static Preferences* getPreferences() {
        if (instance == NULL) {
            instance = new Preferences();
            return instance;
        } else {
            return instance;
        }
    }

    bool loadPreferences(QString dir);
    void savePreverences();
    void addPort(QString port);

    QString         applicationDirectory;
    QStringList     serialPorts;
    QString         currentPort;
    qint32          baudRate;
    qint32          stopBits;
    qint32          parity;
    qint32          dataBits;
    qint32          flowControl;
    quint8          opacity;

    qint32          x;
    qint32          y;
    qint32          width;
    qint32          height;

    bool            timeStamp;
    bool            onTop;
    bool            useEndl;
    bool            scrollList;
    bool            reverseList;
    bool            dtr;

};

#endif // Preferences_H
