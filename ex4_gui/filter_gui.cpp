#include "filter_gui.h"

filter_gui::filter_gui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

filter_gui::filter_gui(mpcap * mp, QWidget * parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->mp = mp;
}

filter_gui::~filter_gui()
{
}

void filter_gui::setFilter() {
	QString option="";
	if (ui.checkBox_protocal->isChecked()) //过滤协议类型
		option += ui.lineEdit_protocal->text() + " ";
	else
		option += "tcp or udp ";
	if (ui.checkBox_port->isChecked())//过滤端口
		option += "port " + ui.lineEdit_port->text()+" ";
	if (ui.checkBox_sip->isChecked())//过滤源地址
		option += "and src host " + ui.lineEdit_sip->text() + " ";
	if (ui.checkBox_dip->isChecked())//过滤目的地址
		option += "and dst host " + ui.lineEdit_dip->text() + " ";
	mp->setFilter(option);
	QMessageBox::information(NULL, "提示", "请重新开始捕获");
	hide();
}
