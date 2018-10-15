#include "GUI_chat.h"

GUI_chat::GUI_chat(msocket &sock,QString &username,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->sock = sock;
	this->username = username;
}

GUI_chat::~GUI_chat()
{
}

void GUI_chat::sendMessage() {
	QString message="CHAT:"+username+";"+ ui.plainTextEdit->toPlainText();
	sock.send(message.toStdString());
	QString disp = QTime::currentTime().toString() + "  ÎÒ:\n"+ ui.plainTextEdit->toPlainText()+"\n\n";
	append(disp);
	ui.plainTextEdit->clear();
}
void GUI_chat::append(QString disp) {
	ui.textBrowser->append(disp);
}

