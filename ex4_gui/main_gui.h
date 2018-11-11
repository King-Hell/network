#pragma once

#include <QtWidgets/QMainWindow>
#include<qmessagebox.h>
#include "ui_main_gui.h"
#include"mpcap.h"
#include"filter_gui.h"
#include"dataThread.h"
#include"data_gui.h"
#include"scan_gui.h"

class main_gui : public QMainWindow
{
	Q_OBJECT

public:
	main_gui(QWidget *parent = Q_NULLPTR);
public slots:
	void flushDev();//ˢ���豸�б�
	void filter_show();//�趨������
	void start(int index);//��ʼץ��
	void start();
	void stop();//ֹͣץ��
	void clear();//��հ��б�
	void getData(QStringList info);
	void closeEvent(QCloseEvent *event);
	void resizeTable();//���µ�������С
	void data_show(int,int);//��ʾ����
	void scan_show();//��ɨ�贰��
private:
	Ui::main_gui ui;
	mpcap mp;
	dataThread *thread;
	filter_gui *filter;
	int rowNum;//�б�����
	int totalNum;//������
};
