/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QGridLayout *gridLayout_2;
    QDialogButtonBox *buttonBox;
    QGridLayout *gridLayout;
    QCheckBox *ckOnTop;
    QCheckBox *ckTimestamp;
    QComboBox *cbFlowControl;
    QCheckBox *ckScroll;
    QLabel *label_6;
    QCheckBox *ckEndLine;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_2;
    QComboBox *cbStopBits;
    QComboBox *cbPort;
    QComboBox *cbData;
    QLabel *label_4;
    QComboBox *cbBaud;
    QComboBox *cbParity;
    QCheckBox *ckReverse;
    QSlider *slOpacity;
    QLabel *label_7;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName("Settings");
        Settings->resize(400, 377);
        gridLayout_2 = new QGridLayout(Settings);
        gridLayout_2->setObjectName("gridLayout_2");
        buttonBox = new QDialogButtonBox(Settings);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        ckOnTop = new QCheckBox(Settings);
        ckOnTop->setObjectName("ckOnTop");

        gridLayout->addWidget(ckOnTop, 7, 0, 1, 1);

        ckTimestamp = new QCheckBox(Settings);
        ckTimestamp->setObjectName("ckTimestamp");

        gridLayout->addWidget(ckTimestamp, 6, 0, 1, 1);

        cbFlowControl = new QComboBox(Settings);
        cbFlowControl->setObjectName("cbFlowControl");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cbFlowControl->sizePolicy().hasHeightForWidth());
        cbFlowControl->setSizePolicy(sizePolicy);
        cbFlowControl->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(cbFlowControl, 5, 0, 1, 1);

        ckScroll = new QCheckBox(Settings);
        ckScroll->setObjectName("ckScroll");

        gridLayout->addWidget(ckScroll, 6, 1, 1, 1);

        label_6 = new QLabel(Settings);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 5, 1, 1, 1);

        ckEndLine = new QCheckBox(Settings);
        ckEndLine->setObjectName("ckEndLine");

        gridLayout->addWidget(ckEndLine, 8, 0, 1, 1);

        label_3 = new QLabel(Settings);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        label_5 = new QLabel(Settings);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 4, 1, 1, 1);

        label = new QLabel(Settings);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 1, 1, 1);

        label_2 = new QLabel(Settings);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        cbStopBits = new QComboBox(Settings);
        cbStopBits->setObjectName("cbStopBits");
        sizePolicy.setHeightForWidth(cbStopBits->sizePolicy().hasHeightForWidth());
        cbStopBits->setSizePolicy(sizePolicy);
        cbStopBits->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(cbStopBits, 4, 0, 1, 1);

        cbPort = new QComboBox(Settings);
        cbPort->setObjectName("cbPort");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(250);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cbPort->sizePolicy().hasHeightForWidth());
        cbPort->setSizePolicy(sizePolicy1);
        cbPort->setMinimumSize(QSize(250, 0));

        gridLayout->addWidget(cbPort, 0, 0, 1, 1);

        cbData = new QComboBox(Settings);
        cbData->setObjectName("cbData");
        sizePolicy.setHeightForWidth(cbData->sizePolicy().hasHeightForWidth());
        cbData->setSizePolicy(sizePolicy);
        cbData->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(cbData, 2, 0, 1, 1);

        label_4 = new QLabel(Settings);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 3, 1, 1, 1);

        cbBaud = new QComboBox(Settings);
        cbBaud->setObjectName("cbBaud");
        sizePolicy.setHeightForWidth(cbBaud->sizePolicy().hasHeightForWidth());
        cbBaud->setSizePolicy(sizePolicy);
        cbBaud->setMinimumSize(QSize(100, 0));
        cbBaud->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(cbBaud, 1, 0, 1, 1);

        cbParity = new QComboBox(Settings);
        cbParity->setObjectName("cbParity");
        sizePolicy.setHeightForWidth(cbParity->sizePolicy().hasHeightForWidth());
        cbParity->setSizePolicy(sizePolicy);
        cbParity->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(cbParity, 3, 0, 1, 1);

        ckReverse = new QCheckBox(Settings);
        ckReverse->setObjectName("ckReverse");

        gridLayout->addWidget(ckReverse, 7, 1, 1, 1);

        slOpacity = new QSlider(Settings);
        slOpacity->setObjectName("slOpacity");
        slOpacity->setMinimum(40);
        slOpacity->setMaximum(100);
        slOpacity->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slOpacity, 9, 0, 1, 1);

        label_7 = new QLabel(Settings);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 9, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(Settings);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Settings, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Settings, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QCoreApplication::translate("Settings", "Dialog", nullptr));
        ckOnTop->setText(QCoreApplication::translate("Settings", "Window on top", nullptr));
        ckTimestamp->setText(QCoreApplication::translate("Settings", "Timestamp", nullptr));
        ckScroll->setText(QCoreApplication::translate("Settings", "Scroll", nullptr));
        label_6->setText(QCoreApplication::translate("Settings", "Flow control", nullptr));
        ckEndLine->setText(QCoreApplication::translate("Settings", "Send end line", nullptr));
        label_3->setText(QCoreApplication::translate("Settings", "Data bits", nullptr));
        label_5->setText(QCoreApplication::translate("Settings", "Stop bits", nullptr));
        label->setText(QCoreApplication::translate("Settings", "Port", nullptr));
        label_2->setText(QCoreApplication::translate("Settings", "Baud rate", nullptr));
        label_4->setText(QCoreApplication::translate("Settings", "Parity", nullptr));
        ckReverse->setText(QCoreApplication::translate("Settings", "Reverse", nullptr));
        label_7->setText(QCoreApplication::translate("Settings", "Opacaity", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
