#include "widget.h"
#include "global.h"

void Widget::SetBaseConfiguration(DeviceInfo *deviceInfo) {
	this->resize(450, 500);
	this->setWindowTitle("Sound Pad");

	QGridLayout *layout = new QGridLayout(this);
	for (int row = 0; row < 5; ++row) {
		if (row == 0)
			layout->setRowStretch(row, 3);
		layout->setRowStretch(row, 1); // устанавливаем высоту строки
		for (int col = 0; col < 4; ++col) {
			layout->setColumnStretch(col, 1); // устанавливаем ширину столбца
			if (row != 0) {
				QPushButton *button = new QPushButton(QString("%1").arg((row - 1) * 4 + col + 1), this);
				button->setStyleSheet("QPushButton { border-radius: 9px;  border: 2px solid black; background-color: " + ButtonColor + ";} \
                    QPushButton:hover { background-color: orange; } \
                    QPushButton:pressed { background-color: silver; }");
				buttons[row - 1][col] = button;
				connect(button, &QPushButton::clicked, this, &Widget::SampleButtonClicked);
				layout->addWidget(button, row, col);
			}
		}
	}

	downloadMenuButton = new QPushButton("Download Disk", this); // menu
	downloadMenuButton->setStyleSheet("QPushButton { ;  border: 4px solid black; background-color: " + ButtonColor + ";} \
    QPushButton:hover { background-color: green; } \
    QPushButton:pressed { background-color: silver; }");

	QMenu *m_menu = new QMenu(downloadMenuButton);
	downloadMenuButton->setMenu(m_menu);
	layout->addWidget(downloadMenuButton, 0, 3);
	foreach (const QStorageInfo &storage, deviceInfo->volumes) {
		QAction *action = new QAction(storage.rootPath(), this);
		m_menu->addAction(action);
		connect(action, &QAction::triggered, this, &Widget::DownloadDiskActionTriggered);
	}

	searchMenuButton = new QPushButton("Search Disk", this); // menu
	searchMenuButton->setStyleSheet("QPushButton { border: 4px solid black; background-color: " + ButtonColor + ";} \
        QPushButton:hover { background-color: green; } \
        QPushButton:pressed { background-color: silver; }");

	QMenu *m_menuSearch = new QMenu(searchMenuButton);
	searchMenuButton->setMenu(m_menuSearch);
	layout->addWidget(searchMenuButton, 0, 2);
	foreach (const QStorageInfo &storage, deviceInfo->volumes) {
		QAction *action = new QAction(storage.rootPath(), this);
		m_menuSearch->addAction(action);
		connect(action, &QAction::triggered, this, &Widget::SearchDiskActionTriggered);
	}

	QPushButton *globalCheckButton = new QPushButton("Global Check", this); // refresh
	globalCheckButton->setStyleSheet("QPushButton { border-radius: 10px; border: 3px solid black; background-color: " + ButtonColor + ";} \
    QPushButton:hover { background-color: green; } \
    QPushButton:pressed { background-color: silver; }");
	connect(globalCheckButton, &QPushButton::clicked, this, &Widget::GlobalCheckClicked);
	layout->addWidget(globalCheckButton, 0, 1);
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
	deviceInfo = new DeviceInfo();
	deviceInfo->GetVolumes();
	SetBaseConfiguration(deviceInfo);
}

void Widget::GlobalCheckClicked() {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			buttons[row][col]->setStyleSheet("QPushButton { border-radius: 9px;  border: 2px solid black; background-color: red;} \
            QPushButton:hover { background-color: orange; } \
            QPushButton:pressed { background-color: silver; }");
		}
	}
	QDir dir(downloadDisk.rootPath());
	QStringList filters;
	filters << "*.mp3";
	QList<QFileInfo> files = dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);
	foreach (QFileInfo fileInfo, files) {
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				if (fileInfo.fileName() == buttons[row][col]->text() + ".mp3") {
					buttons[row][col]->setStyleSheet("QPushButton { border-radius: 9px;  border: 2px solid black; background-color: green;} \
                    QPushButton:hover { background-color: orange; } \
                    QPushButton:pressed { background-color: silver; }");
				}
			}
		}
	}
}

void Widget::DownloadDiskActionTriggered() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (action) {
		foreach (const QStorageInfo &storage, deviceInfo->volumes) {
			if (storage.rootPath() == action->text()) {
				downloadDisk = storage;
				break;
			}
		}
		downloadMenuButton->setText("Download " + action->text());
	}
}

void Widget::SearchDiskActionTriggered() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (action) {
		foreach (const QStorageInfo &storage, deviceInfo->volumes) {
			if (storage.rootPath() == action->text()) {
				searchDisk = storage;
				break;
			}
		}
		searchMenuButton->setText("Search " + action->text());
	}
}

void Widget::SampleButtonClicked() {
	QPushButton *button = qobject_cast<QPushButton *>(sender()); // получаем указатель на кнопку, которая была нажата
	if (button) {
		SampleWidget *sampleWidget = new SampleWidget();
		sampleWidget->SetBaseConfiguration(button, downloadDisk, searchDisk);
		sampleWidget->show();
	}
}

Widget::~Widget() {
}
