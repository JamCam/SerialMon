#ifndef SERIALWATCHER_H
#define SERIALWATCHER_H

#include <QtCore>

//We are looking for this
//#define SEARCH_MANUF_NAME       "FTDI"
//#define SEARCH_DESCRIPTION      "USB Serial Port"
//#define SEARCH_VID              0x403
//#define SEARCH_PID              0x6001
#define SEARCH_MANUF_NAME       "Arduino LLC (www.arduino.cc)"
#define SEARCH_DESCRIPTION      "Arduino Uno"
#define SEARCH_VID              0x2341
#define SEARCH_PID              0x0043

class SerialWatcher : public QThread
{
    Q_OBJECT

public:
    SerialWatcher();
    ~SerialWatcher();

    void run() {
        this->process();
    }

public slots:
    void stop();

signals:
    void deviceConnected(const QString &port);
    void deviceDisconnected(const QString &port);
    //void error(QString err);

private:
    void process();

    //bool                    found;
    bool                    stop_thraed;
    QMutex                  mutex;
    QStringList             ports;
};

#endif // SERIALWATCHER_H
