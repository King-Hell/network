#include "GUI_main.h"
#include<qdebug.h>

GUI_main::GUI_main(msocket &sock, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->sock = sock;
	QObject::connect(&mainRecvThread, &recvThread::sendChat, this, &GUI_main::sendChat);
	QObject::connect(&mainRecvThread, &recvThread::addUser, this, &GUI_main::addUser);
	QObject::connect(&mainRecvThread, &recvThread::deleteUser, this, &GUI_main::deleteUser);
}



void GUI_main::loginSuccess_slot(QString username) {
	show();
	this->username = username;
	ui.label_user->setText("我的用户名：" + username + "    IP地址：" + QString::fromStdString(sock.getAddress()));
	//请求用户列表
	try {
		sock.send("LIST:0");
		QString message = QString::fromStdString(sock.recv());
		QStringList list = message.split(",");
		list.pop_back();
		ui.userListWidget->addItems(list);
		mainRecvThread.init(sock);
		mainRecvThread.start();
	}
	catch (exception) {

	}
}

void GUI_main::sendChat(QString chatTo, QString message) {
	GUI_chat *chat = NULL;
	if (chatWindow.find(chatTo) == chatWindow.end()) {
		//未开启与该用户的聊天窗口
		chat = new GUI_chat(sock, chatTo,&chatWindow);
		chatWindow.insert(chatTo, chat);
		chat->show();
	}
	else {
		//已开启与该用户的聊天窗口
		chat = chatWindow.find(chatTo).value();
	}
	chat->append(message);
}

void GUI_main::addUser(QString chatTo) {
	QList<QListWidgetItem *> list = ui.userListWidget->findItems(chatTo, Qt::MatchExactly);
	if (list.size() == 0)
		ui.userListWidget->addItem(chatTo);
}

void GUI_main::deleteUser(QString chatTo) {
	QList<QListWidgetItem *> list = ui.userListWidget->findItems(chatTo, Qt::MatchExactly);
	if (list.size() == 1) {
		int row = ui.userListWidget->row(list[0]);
		ui.userListWidget->takeItem(row);
	}
		
}

GUI_main::~GUI_main()
{
}

void GUI_main::beginChat(QListWidgetItem *item) {
	//请求与某人聊天
	QString username = item->text();
	GUI_chat *chat = new GUI_chat(sock, username,&chatWindow);
	chatWindow.insert(username, chat);
	chat->show();
}

void GUI_main::closeEvent(QCloseEvent *event)
{
	sock.send("LOGOUT:0");
	mainRecvThread.stop();
	mainRecvThread.terminate();
	sock.close();
	for (auto i = chatWindow.begin(); i != chatWindow.end(); i++)
		i.value()->close();
}


