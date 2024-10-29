#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

#include "serialwatcher.h"
#include "preferences.h"

#define PATH_TOK_END        -4
#define PATH_TOK_START      0
#define PATH_SEPARATOR      "/"

#ifdef Q_OS_WIN
#ifdef QT_DEBUG
#define PATH_TOK_END        -2
#else
#define PATH_TOK_END        -1
#endif
#else
#ifdef QT_DEBUG
#define PATH_TOK_END        -5
#else
#define PATH_TOK_END        -4
#endif
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onDeviceConnect(const QString &port);
    void onDeviceDisconnect(const QString &port);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);
    void clearLines();
    void actionSettings();
    void actionSave();
    void edReturnPressed();

private:
    Ui::MainWindow *ui;
    QSerialPort         m_serialPort;

    QString             m_selectedPort;
    QStringList         m_Ports;

    Preferences         *preferences;
    QString             settingsDirectory;

    SerialWatcher       watcher;

    QString             dataDirectory;
    bool                portOpen;

    void serialOpen();
    void setOnTop(int state);
};
#endif // MAINWINDOW_H
