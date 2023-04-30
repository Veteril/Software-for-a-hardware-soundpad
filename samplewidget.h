
#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QInputDialog>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDir>
#include <QStorageInfo>

class SampleWidget:public QWidget
{
    Q_OBJECT

public:
    SampleWidget(QWidget *parent = nullptr);
    ~SampleWidget();

    void SetBaseConfiguration(QPushButton * button, QStorageInfo disk, QStorageInfo searchDisk);
    void SearchSuitableMP3Files();

    QStorageInfo downloadDisk;
    QStorageInfo searchDisk;
    QPushButton * sampleButton;
    QListWidget *listWidgetMain;
    QListWidget *listWidgetChild;
    QList<QFileInfo> files;
private slots:

    void RenameButtonClicked();
    void AddFileButtonClicked();
    void AddButtonClicked();
};

#endif // SAMPLEWIDGET_H
