#include "scan_gui.h"

scan_gui::scan_gui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}
scan_gui::scan_gui(mpcap *mp, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->mp = mp;
}

scan_gui::~scan_gui()
{
}

void scan_gui::showOpen()
{
	QSet<int> list = mp->getOpen();
	for (auto i = list.begin(); i != list.end(); i++)
		ui.plainTextEdit->appendPlainText(QString::number(*i));
}

void scan_gui::scan()
{//É¨Ãè

	QStringList list = ui.lineEdit->text().split('.');
	ip_address dip;
	dip.byte1 = list[0].toUInt();
	dip.byte2 = list[1].toUInt();
	dip.byte3 = list[2].toUInt();
	dip.byte4 = list[3].toUInt();
	for (int i = 0; i < 1023; i++)
		mp->sendSyn(dip, i);
}
