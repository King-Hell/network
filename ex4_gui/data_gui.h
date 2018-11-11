#pragma once

#include <QWidget>
#include "ui_data_gui.h"

class data_gui : public QWidget
{
	Q_OBJECT

public:
	data_gui(QWidget *parent = Q_NULLPTR);
	data_gui( int length,unsigned char *content,QWidget *parent = Q_NULLPTR);
	~data_gui();

private:
	Ui::data_gui ui;
};
