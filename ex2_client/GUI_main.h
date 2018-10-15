#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_GUI_main.h"
#include "msocket.h"
#include "GUI_chat.h"
#include "mThread.h"

class GUI_main : public QMainWindow
{
	Q_OBJECT

public:
	GUI_main(msocket&, QWidget *parent = Q_NULLPTR);
	~GUI_main();
	void closeEvent(QCloseEvent *event);
public slots:
	void loginSuccess_slot(QString);
	void beginChat(QListWidgetItem *item);
	void sendChat(QString chatTo, QString message);//�������촰��
	void addUser(QString chatTo);//�����û�
	void deleteUser(QString chatTo);//ɾ���û�
private:
	Ui::GUI_main ui;
	msocket sock;
	QString username;
	QMap<QString, GUI_chat*> chatWindow;
	recvThread mainRecvThread;
};
