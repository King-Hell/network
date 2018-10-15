#pragma once

#include <QWidget>
#include <qmessagebox.h>

#include "ui_GUI_login.h"
#include "msocket.h"


class GUI_login : public QWidget
{
	Q_OBJECT

public:
	GUI_login(msocket&,QWidget *parent = Q_NULLPTR);
	~GUI_login();

signals:
	void loginSuccess(QString);//��¼�ɹ��ź�
public slots:
	void login();//��¼����

private:
	Ui::GUI_login ui;
	msocket sock;
};
