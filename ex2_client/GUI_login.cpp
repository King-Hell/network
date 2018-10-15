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

void GUI_login::login() {//��¼��ⷽ��
	// �������������������
	if (ui.edit_username->text() == "" || ui.edit_password->text() == "") {
		sock.error(string("�û��������벻��Ϊ��"));
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
			sock.error(string("��¼ʧ��"));
	}
	catch(exception) {

	}
}