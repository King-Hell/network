#pragma once

#include <QWidget>
#include "ui_scan_gui.h"
#include"mpcap.h"

class scan_gui : public QWidget
{
	Q_OBJECT

public:
	scan_gui(QWidget *parent = Q_NULLPTR);
	scan_gui(mpcap *mp,QWidget *parent = Q_NULLPTR);
	~scan_gui();
public slots:
	void scan();
	void showOpen();

private:
	Ui::scan_gui ui;
	mpcap *mp;
};
