#include "serialwatcher.h"
#include <QtSerialPort/QSerialPortInfo>

#ifdef Q_OS_WIN
#include <windows.h>
#include <fileapi.h>
#include <winreg.h>
#endif
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383


SerialWatcher::SerialWatcher()
{
    stop_thraed = false;
}

SerialWatcher::~SerialWatcher()
{
    stop();
}

void SerialWatcher::process()
{
    while(1) {
        msleep(10);
        QMutexLocker locker(&mutex);
        if(stop_thraed) {
            break;
        }

        QStringList found;

#ifdef Q_OS_WIN
        //msleep(300);
        /*
        HKEY hKey;
        long lret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &hKey);

        if(lret == ERROR_SUCCESS ) {

            BYTE buf[MAX_VALUE_NAME];
            TCHAR acValueName[MAX_VALUE_NAME];
            DWORD dwValueNameLen = MAX_VALUE_NAME;
            DWORD dwType;
            DWORD dwSize = MAX_VALUE_NAME;
            DWORD dwIdx = 0;

            lret = RegEnumValue(hKey, dwIdx, acValueName, &dwValueNameLen, NULL, &dwType, (LPBYTE)buf, &dwSize);
            while (ERROR_SUCCESS == lret)
            {

                QString fc = QString::fromWCharArray((wchar_t *)buf);
                found << fc;
                if(!ports.contains(fc)) {
                    qDebug() << "Found " << fc;
                    ports << fc;
                    emit deviceConnected(fc);
                }
                //qDebug() << dwIdx << QString::fromWCharArray((wchar_t *)acValueName) << " - " << QString::fromWCharArray((wchar_t *)buf);
                dwIdx++;
                dwSize = MAX_VALUE_NAME;
                dwValueNameLen = MAX_VALUE_NAME;
                lret = RegEnumValue(hKey, dwIdx, acValueName, &dwValueNameLen, NULL, &dwType, (LPBYTE)buf, &dwSize);
            }

            RegCloseKey(hKey);
        }
*/
        TCHAR  lpTargetPath[MAX_PATH]; // buffer to store the path of the COMPORTS
        long test;
        bool gotPort = 0; // in case the port is not found

        for(int i = 0; i < 50; i++) // checking ports from COM0 to COM255
        {
            WCHAR buf[MAX_PATH];
            QString com = "COM" + QString::number(i);
            com.toWCharArray(buf);

            // Test the return value and error if any
            test = QueryDosDevice((LPCWSTR)buf, lpTargetPath, MAX_PATH);
            //qDebug() << test;
            if(test) //QueryDosDevice returns zero if it didn't find an object
            {
                found << com;
                if(!ports.contains(com)) {
                    qDebug() << "Found " << com;
                    ports << com;
                    emit deviceConnected(com);
                }
            }

        }
        //qDebug() << found.length() <<  " ++ " << ports.count();
#else
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {

            /*
             qDebug() << tr("vendorIdentifier %1").arg(info.vendorIdentifier());
             qDebug() << tr("productIdentifier %1").arg(info.productIdentifier());
             qDebug() << tr("manufacturer %1").arg(info.manufacturer());
             qDebug() << tr("description %1").arg(info.description());
             qDebug() << tr("systemLocation %1").arg(info.systemLocation());
             qDebug() << tr("portName %1").arg(info.portName());
            if((info.hasVendorIdentifier() && info.vendorIdentifier() == SEARCH_VID) && (info.hasProductIdentifier() && info.productIdentifier() == SEARCH_PID)) {
                //qDebug() << tr("vendorIdentifier %1").arg(info.vendorIdentifier());
                //qDebug() << tr("productIdentifier %1").arg(info.productIdentifier());
                if(info.description().compare(SEARCH_DESCRIPTION) == 0 && info.manufacturer().compare(SEARCH_MANUF_NAME) == 0) {
                    //qDebug() << tr("manufacturer %1").arg(info.manufacturer());
                    //qDebug() << tr("description %1").arg(info.description());
                    //qDebug() << tr("SN %1").arg(info.serialNumber());

                    found << info.portName();
                    if(!ports.contains(info.portName())) {
                        ports << info.portName();
                        emit deviceConnected(info.portName());
                    }
                }
            }
*/

            found << info.portName();
            if(!ports.contains(info.portName())) {
                ports << info.portName();
                emit deviceConnected(info.portName());
            }
        }
#endif
        //qDebug() << found.length() <<  " < " << ports.count();
        if(found.length() < ports.count()) {
            foreach (QString p, ports) {
                if(!found.contains(p)) {
                    qDebug() << "Lost " << p;
                    ports.removeAll(p);
                    emit deviceDisconnected(p);
                }
            }
        }

    }
}

void SerialWatcher::stop()
{
    qDebug()<<"Thread::stop called from main thread: "<<currentThreadId();
    QMutexLocker locker(&mutex);
    stop_thraed = true;
}

