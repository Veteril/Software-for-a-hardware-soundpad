#include <QtCore/QStorageInfo>
#include <QStorageInfo>
#include <QtCore/QDebug>

#ifndef DEVICEINFO_H
#define DEVICEINFO_H




class DeviceInfo
{

public:

    DeviceInfo();
    void GetVolumes();
    QList<QStorageInfo> volumes;
};

#endif // DEVICEINFO_H
