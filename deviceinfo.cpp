
#include "deviceinfo.h"

DeviceInfo::DeviceInfo(){}

void DeviceInfo::GetVolumes()
{
    this->volumes = QStorageInfo::mountedVolumes();
    foreach (const QStorageInfo &storage, volumes) {
        if (storage.isReady() && storage.isValid() && !storage.isReadOnly()) {
            qDebug() << "Drive:" << storage.rootPath();
        }
    }
}

