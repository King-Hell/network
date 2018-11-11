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
	if (ui.checkBox_protocal->isChecked()) //����Э������
		option += ui.lineEdit_protocal->text() + " ";
	else
		option += "tcp or udp ";
	if (ui.checkBox_port->isChecked())//���˶˿�
		option += "port " + ui.lineEdit_port->text()+" ";
	if (ui.checkBox_sip->isChecked())//����Դ��ַ
		option += "and src host " + ui.lineEdit_sip->text() + " ";
	if (ui.checkBox_dip->isChecked())//����Ŀ�ĵ�ַ
		option += "and dst host " + ui.lineEdit_dip->text() + " ";
	mp->setFilter(option);
	QMessageBox::information(NULL, "��ʾ", "�����¿�ʼ����");
	hide();
}
