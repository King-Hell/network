#include "GUI_login.h"

GUI_login::GUI_login(msocket &sock, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->sock = sock;
}

GUI_login::~GUI_login()
{
	
}

void GUI_login::login() {//登录检测方法
	// 向服务器发出连接请求
	if (ui.edit_username->text() == "" || ui.edit_password->text() == "") {
		sock.error(string("用户名或密码不可为空"));
		return;
	}
	QString username = ui.edit_username->text();
	QString password = ui.edit_password->text();
	QString message = "LOGIN:"+username + "," + password;
	try {
		sock.connect();
		sock.send(message.toStdString());
		if (sock.recv() == string("SUCCESS")) {
			emit loginSuccess(username);
			close();
		}
		else
			sock.error(string("登录失败"));
	}
	catch(exception) {

	}
}