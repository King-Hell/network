#include <QtWidgets/QApplication>

#include "GUI_main.h"
#include "GUI_login.h"
#include "msocket.h"
using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	msocket sock("118.89.240.19",5099);
	GUI_main w(sock);//主窗口
	GUI_login login(sock);//登录界面
	QObject::connect(&login, &GUI_login::loginSuccess, &w, &GUI_main::loginSuccess_slot);
	login.show();//显示登录界面
	return a.exec();
}
