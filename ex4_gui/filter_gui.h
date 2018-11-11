#pragma once

#include <QWidget>
#include<qmessagebox.h>
#include "ui_filter_gui.h"
#include"mpcap.h"

class filter_gui : public QWidget
{
	Q_OBJECT

public:
	filter_gui(QWidget *parent = Q_NULLPTR);
	filter_gui(mpcap *mp,QWidget *parent = Q_NULLPTR);
	~filter_gui();
public slots:
	void setFilter();
private:
	Ui::filter_gui ui;
	mpcap *mp;
};
