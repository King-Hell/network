#include "main_gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	main_gui w;
	w.show();
	return a.exec();
}
