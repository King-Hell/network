#include <QtWidgets/QApplication>

#include "GUI_main.h"
#include "GUI_login.h"
#include "msocket.h"
using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	msocket sock("118.89.240.19",5099);
	GUI_main w(sock);//������
	GUI_login login(sock);//��¼����
	QObject::connect(&login, &GUI_login::loginSuccess, &w, &GUI_main::loginSuccess_slot);
	login.show();//��ʾ��¼����
	return a.exec();
}
