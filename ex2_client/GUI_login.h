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
	void loginSuccess(QString);//登录成功信号
public slots:
	void login();//登录方法

private:
	Ui::GUI_login ui;
	msocket sock;
};
