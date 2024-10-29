#include "preferences.h"


Preferences::Preferences()
{

}

Preferences::~Preferences()
{
    //savePreverences();
}

bool Preferences::loadPreferences(QString dir)
{
    applicationDirectory = dir;
    QString val;
    QString fp = applicationDirectory + "/preferences.json";
    qDebug() << fp;
    QFile file;
    file.setFileName(fp);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject prefs = d.object();
    QJsonObject serial = d["port"].toObject();

    currentPort = serial["port"].toString("");;
    baudRate = serial["baud"].toInt(115200);
    stopBits = serial["stop"].toInt(1);
    parity = serial["parity"].toInt(0);
    dataBits = serial["data"].toInt(8);
    flowControl = serial["flow"].toInt(0);

    timeStamp = prefs["timestamp"].toInt(0);
    onTop = prefs["ontop"].toInt(0);
    useEndl = prefs["endline"].toInt(0);
    scrollList = prefs["scroll"].toInt(0);
    reverseList = prefs["reverse"].toInt(0);
    opacity = prefs["opacity"].toInt(100);
    dtr = prefs["dtr"].toInt(1);

    x = prefs["x"].toInt(0);
    y = prefs["y"].toInt(0);
    width = prefs["width"].toInt(0);
    height = prefs["height"].toInt(0);

    qDebug() << "currentPort" << currentPort;
    qDebug() << "baudRate" << baudRate;
    qDebug() << "stopBits" << stopBits;
    qDebug() << "parity" << parity;
    qDebug() << "dataBits" << dataBits;
    qDebug() << "flowControl" << flowControl;
    qDebug() << "timeStamp" << timeStamp;
    qDebug() << "onTop" << onTop;
    qDebug() << "useEndl" << useEndl;
    qDebug() << "scroll" << scrollList;
    qDebug() << "reverse" << reverseList;
    qDebug() << "opacity" << opacity;

    return true;
}

void Preferences::savePreverences()
{
    QFile file;
    QJsonObject prefs;

    QJsonObject port;

    port["port"] = currentPort;
    port["baud"] = baudRate;
    port["stop"] = stopBits;
    port["parity"] = parity;
    port["data"] = dataBits;
    port["flow"] = flowControl;

    prefs["port"] = port;
    prefs["timestamp"] = int(timeStamp);
    prefs["ontop"] = int(onTop);
    prefs["endline"] = int(useEndl);
    prefs["scroll"] = int(scrollList);
    prefs["reverse"] = int(reverseList);
    prefs["opacity"] = int(opacity);
    prefs["dtr"] = int(dtr);

    prefs["x"] = x;
    prefs["y"] = y;
    prefs["width"] = width;
    prefs["height"] = height;

    QJsonDocument d(prefs);
    //qDebug() << d.toJson();

    QString fp = applicationDirectory + "/preferences.json";
    file.setFileName(fp);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(d.toJson());
    file.close();

}

void Preferences::addPort(QString port)
{
    //qDebug() << recentFiles;
    //qDebug() << path;
    if(serialPorts.contains(port)) {
        //qDebug() << "found";
        return;
    }
    serialPorts.append(port);
    qDebug() << serialPorts;
}
