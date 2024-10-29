#include "settings.h"
#include "ui_settings.h"
#include <QtSerialPort/QSerialPort>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    preferences = Preferences::getPreferences();

    ui->cbParity->addItem("NoParity", QSerialPort::NoParity);
    ui->cbParity->addItem("EvenParity", QSerialPort::EvenParity);
    ui->cbParity->addItem("OddParity", QSerialPort::OddParity);
    ui->cbParity->addItem("SpaceParity", QSerialPort::SpaceParity);
    ui->cbParity->addItem("MarkParity", QSerialPort::MarkParity);

    qint32 val = ui->cbParity->findData(preferences->parity);
    if(val > -1) {
        ui->cbParity->setCurrentIndex(val);
    } else {
        ui->cbParity->setCurrentIndex(0);
    }

    ui->cbBaud->addItem("1200", 1200);
    ui->cbBaud->addItem("2400", 2400);
    ui->cbBaud->addItem("4800", 4800);
    ui->cbBaud->addItem("9600", 9600);
    ui->cbBaud->addItem("19200", 19200);
    ui->cbBaud->addItem("38400", 38400);
    ui->cbBaud->addItem("57600", 57600);
    ui->cbBaud->addItem("115200", 115200);

    val = ui->cbBaud->findData(preferences->baudRate);
    if(val > -1) {
        ui->cbBaud->setCurrentIndex(val);
    } else {
        ui->cbBaud->setCurrentIndex(0);
    }

    ui->cbData->addItem("5", 5);
    ui->cbData->addItem("6", 6);
    ui->cbData->addItem("7", 7);
    ui->cbData->addItem("8", 8);

    val = ui->cbData->findData(preferences->dataBits);
    if(val > -1) {
        ui->cbData->setCurrentIndex(val);
    } else {
        ui->cbData->setCurrentIndex(0);
    }


    ui->cbStopBits->addItem("1", 1);
    ui->cbStopBits->addItem("2", 2);
    ui->cbStopBits->addItem("3", 3);

    val = ui->cbStopBits->findData(preferences->stopBits);
    if(val > -1) {
        ui->cbStopBits->setCurrentIndex(val);
    } else {
        ui->cbStopBits->setCurrentIndex(0);
    }

    ui->cbFlowControl->addItem("No Control", 0);
    ui->cbFlowControl->addItem("Hardware", 1);
    ui->cbFlowControl->addItem("Software", 2);

    val = ui->cbFlowControl->findData(preferences->flowControl);
    if(val > -1) {
        ui->cbFlowControl->setCurrentIndex(val);
    } else {
        ui->cbFlowControl->setCurrentIndex(0);
    }

    ui->cbPort->clear();

    foreach(QString p, preferences->serialPorts) {
        ui->cbPort->addItem(p, p);
    }

    val = ui->cbPort->findData(preferences->currentPort);
    if(val > -1) {
        ui->cbPort->setCurrentIndex(val);
    }

    if(preferences->timeStamp) {
        ui->ckTimestamp->setCheckState(Qt::Checked);
    } else {
        ui->ckTimestamp->setCheckState(Qt::Unchecked);
    }

    if(preferences->onTop) {
        ui->ckOnTop->setCheckState(Qt::Checked);
    } else {
        ui->ckOnTop->setCheckState(Qt::Unchecked);
    }

    if(preferences->useEndl) {
        ui->ckEndLine->setCheckState(Qt::Checked);
    } else {
        ui->ckEndLine->setCheckState(Qt::Unchecked);
    }

    if(preferences->scrollList) {
        ui->ckScroll->setCheckState(Qt::Checked);
    } else {
        ui->ckScroll->setCheckState(Qt::Unchecked);
    }

    if(preferences->reverseList) {
        ui->ckReverse->setCheckState(Qt::Checked);
    } else {
        ui->ckReverse->setCheckState(Qt::Unchecked);
    }

    if(preferences->dtr) {
        ui->ckDTR->setCheckState(Qt::Checked);
    } else {
        ui->ckDTR->setCheckState(Qt::Unchecked);
    }

    ui->slOpacity->setSliderPosition(preferences->opacity);
}

 void Settings::accept()
{
    preferences->parity = ui->cbParity->currentData().toLongLong();
    preferences->baudRate = ui->cbBaud->currentData().toLongLong();
    preferences->dataBits = ui->cbData->currentData().toLongLong();
    preferences->stopBits = ui->cbStopBits->currentData().toLongLong();
    preferences->flowControl = ui->cbFlowControl->currentData().toLongLong();
    preferences->currentPort = ui->cbPort->currentData().toString();
    preferences->timeStamp = ui->ckTimestamp->isChecked();
    preferences->onTop = ui->ckOnTop->isChecked();
    preferences->useEndl = ui->ckEndLine->isChecked();
    preferences->scrollList = ui->ckScroll->isChecked();
    preferences->reverseList = ui->ckReverse->isChecked();
    preferences->opacity = ui->slOpacity->sliderPosition();
    done(1);
}

Settings::~Settings()
{
    delete ui;
}
