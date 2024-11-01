#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "preferences.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
    Preferences *preferences;

    void accept();
};

#endif // SETTINGS_H
