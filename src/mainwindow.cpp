#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settings.h"

#include <QDebug>
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList dirs = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    settingsDirectory = dirs[0];

    if(!QDir(settingsDirectory).exists()) {
        QDir().mkdir(settingsDirectory);
    }
    dirs = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    dataDirectory = dirs[0];

    //applicationDirectory =  QDir().absolutePath().section(PATH_SEPARATOR, PATH_TOK_START, PATH_TOK_END);
    preferences = Preferences::getPreferences();
    preferences->loadPreferences(settingsDirectory);

    m_selectedPort = preferences->currentPort;
    setOnTop(preferences->onTop);
    if(preferences->height) {
        move(preferences->x, preferences->y);
        resize(preferences->width, preferences->height);
    }
    portOpen = false;

    connect(&m_serialPort, SIGNAL(readyRead()), SLOT(handleReadyRead()));
    //connect(&m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(handleError(QSerialPort::SerialPortError)));
    connect(&m_serialPort, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

    connect(&watcher, SIGNAL(deviceConnected(QString)), this, SLOT(onDeviceConnect(QString)));
    connect(&watcher, SIGNAL(deviceDisconnected(QString)), this, SLOT(onDeviceDisconnect(QString)));

    connect(ui->actionThings, &QAction::triggered, this, &MainWindow::actionSettings);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::actionSave);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::clearLines);
    connect(ui->txtCommand, &QLineEdit::returnPressed, this, &MainWindow::edReturnPressed);

    connect(ui->butClear, &QPushButton::pressed, this, &MainWindow::clearLines);

    setWindowOpacity(float(preferences->opacity)/100.0);

    watcher.start();
}

MainWindow::~MainWindow()
{
    watcher.stop();
    watcher.wait();
    m_serialPort.close();
    delete ui;
}


void MainWindow::onDeviceConnect(const QString &port)
{
    qDebug() << port << " connected";

    preferences->addPort(port);
    if(port.compare(m_selectedPort) == 0) {
        serialOpen();
    }
}

void MainWindow::onDeviceDisconnect(const QString &port)
{
    qDebug() << port << " disconnected";
    if(port.compare(m_selectedPort) == 0) {
        m_serialPort.close();
        qDebug() << "Closed " << m_selectedPort << Qt::endl;
        ui->statusbar->showMessage("Closed " + m_selectedPort);
    }
}

void MainWindow::serialOpen()
{
    m_serialPort.close();

    qDebug() << m_selectedPort;
    portOpen = false;

    m_serialPort.setPortName(m_selectedPort);

    m_serialPort.setBaudRate(preferences->baudRate);
    m_serialPort.setDataBits((QSerialPort::DataBits)preferences->dataBits);
    m_serialPort.setStopBits((QSerialPort::StopBits)preferences->stopBits);
    m_serialPort.setFlowControl((QSerialPort::FlowControl)preferences->flowControl);
    m_serialPort.setParity((QSerialPort::Parity)preferences->parity);

    if (!m_serialPort.open(QIODeviceBase::ReadWrite)) {
        qDebug() << "Serial failed to open "  << m_selectedPort << Qt::endl;
        ui->statusbar->showMessage("Failed to open " + m_selectedPort);
    } else {
        if(preferences->dtr) {
            m_serialPort.setDataTerminalReady(true);
        }
        portOpen = true;
        qDebug() << "Opened " << m_selectedPort << Qt::endl;
        QString par = "N";
        switch(preferences->parity) {
            case QSerialPort::EvenParity:
                par = "Even";
                break;
            case QSerialPort::OddParity:
                par = "Odd";
                break;
            case QSerialPort::SpaceParity:
                par = "Space";
                break;
            case QSerialPort::MarkParity:
                par = "Mark";
                break;
        }

        ui->statusbar->showMessage("Opened " + m_selectedPort +" (" +
                                   QString::number(preferences->baudRate) + " " +
                                   QString::number(preferences->dataBits) + " " +
                                   par + " " +
                                   QString::number(preferences->stopBits) + ")"
                                   );
    }
}

void MainWindow::setOnTop(int state)
{
    Qt::WindowFlags flags = windowFlags();
    if(state) {
        setWindowFlags(flags | Qt::WindowStaysOnTopHint);
        show();
    } else {
        setWindowFlags(flags & (~Qt::WindowStaysOnTopHint));
        show();
    }
}

void MainWindow::actionSettings()
{
    Settings set(this);
    if(set.exec()) {
        m_selectedPort = preferences->currentPort;
        setOnTop(preferences->onTop);
        serialOpen();
        preferences->savePreverences();
        setWindowOpacity(float(preferences->opacity)/100.0);
    }
    //set.close();
}

void MainWindow::actionSave()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    dataDirectory + "/untitled.txt",
                                                    tr("Text (*.txt)"));
    if(fileName.length()) {
        QFile file;
        QString text;
        for(int i = 0; i < ui->lstSerial->count(); i++) {
                text.append(ui->lstSerial->item(i)->text() + "\n");
        }
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(text.toUtf8());
        file.close();
    }
}

void MainWindow::edReturnPressed()
{
    QString s = ui->txtCommand->displayText();
    if(s.length()) {
        if(portOpen) {
            if(preferences->useEndl) {
                s = s + "\n";
                qDebug() << s;
            }
            m_serialPort.write(s.toUtf8());
        }
    }
    ui->txtCommand->clear();
}

void MainWindow::handleReadyRead()
{
    //qDebug() << line;
}

void MainWindow::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        qDebug() << "An I/O error occurred while reading the data" << Qt::endl;
        QCoreApplication::exit(1);
    }
}

void MainWindow::clearLines()
{
    ui->lstSerial->clear();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    preferences->x = pos().x();
    preferences->y = pos().y();

    preferences->width = rect().width();
    preferences->height = rect().height();

    preferences->savePreverences();

    watcher.stop();
    watcher.wait();
    m_serialPort.close();
    event->accept();
}
