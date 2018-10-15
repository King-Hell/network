#pragma once

#include <QWidget>
#include "ui_GUI_chat.h"
#include "msocket.h"
#include <qdatetime.h>

class GUI_chat : public QWidget
{
	Q_OBJECT

public:
	GUI_chat(msocket&,QString&,QWidget *parent = Q_NULLPTR);
	~GUI_chat();
	void append(QString);
public slots:
	void sendMessage();
private:
	Ui::GUI_chat ui;
	msocket sock;
	QString username;

};
