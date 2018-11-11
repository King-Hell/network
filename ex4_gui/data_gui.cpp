#include "data_gui.h"

data_gui::data_gui(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

data_gui::data_gui(int length, unsigned char *content, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	char a[3 * 16+1];
	for (int k = 0, i = 0; k < length; k++, i++) {
		if (k % 16 == 0 && k != 0) {//Êä³öÃÀ¹Û
			a[3 * 16] = 0;
			ui.plainTextEdit->appendPlainText(a);
			i = 0;
		}
		sprintf(a + i * 3, "%02x ", *(content + k));
	}
	if (length % 16 != 0)
		ui.plainTextEdit->appendPlainText(a);
}

data_gui::~data_gui()
{
}
