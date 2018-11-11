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
	void flushDev();//刷新设备列表
	void filter_show();//设定过滤器
	void start(int index);//开始抓包
	void start();
	void stop();//停止抓包
	void clear();//清空包列表
	void getData(QStringList info);
	void closeEvent(QCloseEvent *event);
	void resizeTable();//重新调整表格大小
	void data_show(int,int);//显示数据
	void scan_show();//打开扫描窗口
private:
	Ui::main_gui ui;
	mpcap mp;
	dataThread *thread;
	filter_gui *filter;
	int rowNum;//列表行数
	int totalNum;//总行数
};
