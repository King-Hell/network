#include"msocketServer.h"
#include<windows.h>
#include<sql.h>
#include <sqlext.h>
#include<map>
#include<vector>
#include<string>

map<string, msocket*> userList;//用户列表

SQLHENV serverhenv;
SQLHDBC serverhdbc;
SQLHSTMT serverhstmt;
SQLRETURN ret;
SQLLEN length;

std::vector<std::string> split(std::string &str, std::string &pattern) {
	//分割字符串方法
	std::vector<std::string> resVec;
	if ("" == str)
		return resVec;
	//方便截取最后一段数据
	size_t pos = str.find(pattern);
	size_t size = str.size();
	std::string x = str.substr(0, pos);
	resVec.push_back(x);
	str = str.substr(pos + 1, size);
	resVec.push_back(str);
	return resVec;
}
bool checkUser(const char *name, const char *pass) {
	//查询用户名和密码
	SQLCHAR password[255];
	string select = "select password from user where username='" + (string)name + "';";
	//分配执行语句句柄
	ret = SQLAllocHandle(SQL_HANDLE_STMT, serverhdbc, &serverhstmt);
	//执行SQL语句
	ret = SQLExecDirect(serverhstmt, (SQLCHAR*)select.c_str(), SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		//绑定数据
		SQLBindCol(serverhstmt, 1, SQL_C_CHAR, (void*)password, sizeof(password), &length);
		//将光标移动到下行,即获得下行数据
		if (userList.find(name) == userList.end())
			cout << 12313 << endl;
		if (SQL_NO_DATA != SQLFetch(serverhstmt) && strcmp((char*)password, pass) == 0 && userList.find(name) == userList.end())
			return true;
	}
	return false;
}

DWORD WINAPI clientThread(LPVOID args) {
	msocket *sock = (msocket*)args;
	string ip = sock->getAddress();
	cout << ip << ":已连接" << endl;
	string user = "";
	try {
		while (true) {
			//转发消息
			string message = sock->recv();
			string pattern = ":";
			vector<string> str = split(message, pattern);
			string ins = str[0];
			string content = str[1];
			cout << "请求：" << ins << "内容" << content << endl;
			if (ins == "LOGIN") {
				//请求登录
				const char *username = NULL, *password;
				string pattern = ",";
				vector<string> info = split(content, pattern);
				username = info[0].c_str();//用户名
				password = info[1].c_str();//密码
				user = username;
				if (checkUser(username, password)) {
					sock->send(string("SUCCESS"));
					for (auto i = userList.begin(); i != userList.end(); i++) 
							(*i).second->send("INFO:LOGIN;" + user);//让所有客户端刷新用户列表
					userList.insert(pair<string, msocket*>(username, sock));
					cout << ip << ":已登录,用户名:" << username << endl;
				}
				else {
					sock->send(string("FAILURE"));
					cout << ip << ":拒绝访问,用户名:" << username << endl;
					break;
				}
			}
			else if (ins == "LIST") {
				//请求用户列表
				message = "";
				for (auto i = userList.begin(); i != userList.end(); i++)
					message += (*i).first + ",";
				sock->send(message);
				cout << ip << "请求用户列表" << endl;
			}
			else if (ins == "CHAT") {
				//请求聊天
				string pattern = ";";
				vector<string> info = split(content, pattern);
				string chatTo = info[0];
				string chatContent = info[1];
				if (userList.find(chatTo) != userList.end()) {
					//要聊天的对象在线
					msocket *chatSocket = userList.find(chatTo)->second;
					chatSocket->send("CHAT:" + user + ";" + chatContent + "\n");
				}
				else {
					//要聊天的对象离线
					sock->send("CHAT:system;" + chatTo + "已离线\n");
				}
			}
			else if (ins == "LOGOUT") {
				//请求退出
				userList.erase(user);
				for (auto i = userList.begin(); i != userList.end(); i++)
					(*i).second->send("INFO:LOGOUT;" + user);//让所有客户端刷新用户列表
				cout << ip << user << "退出" << endl;
				break;
			}
		}
		sock->close();
		return 0;
	}
	catch (exception) {
		sock->close();
		cout << ip << "异常退出" << endl;
		if (user != "" && userList.find(user) != userList.end()) {
			userList.erase(user);
			for (auto i = userList.begin(); i != userList.end(); i++)
				(*i).second->send("INFO:LOGOUT;" + user);//让所有客户端刷新用户列表
		}
		return -1;
	}

}

void mysqlInit() {

	//分配环境句柄
	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &serverhenv);
	//设置环境属性
	ret = SQLSetEnvAttr(serverhenv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (!SQL_SUCCEEDED(ret)) {
		cout << "AllocEnvHandle error!" << endl;
		return;
	}
	//分配连接句柄
	ret = SQLAllocHandle(SQL_HANDLE_DBC, serverhenv, &serverhdbc);
	if (!SQL_SUCCEEDED(ret)) {
		cout << "AllocDbcHandle error!" << endl;
		return;
	}
	//数据库连接
	ret = SQLConnect(serverhdbc, (SQLCHAR*)"network_ex2", SQL_NTS, (SQLCHAR*)"network", SQL_NTS, (SQLCHAR*)"1234", SQL_NTS);//第二个参数是之前配置的数据源，后面是数据库用户名和密码
	if (!SQL_SUCCEEDED(ret)) {
		cout << "SQL_Connect error!" << endl;
		return;
	}
}
void mysqlClean() {
	//释放语句句柄
	ret = SQLFreeHandle(SQL_HANDLE_STMT, serverhstmt);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
		cout << "free hstmt error!" << endl;
	//断开数据库连接
	ret = SQLDisconnect(serverhdbc);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
		cout << "disconnected error!" << endl;
	//释放连接句柄
	ret = SQLFreeHandle(SQL_HANDLE_DBC, serverhdbc);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
		cout << "free hdbc error!" << endl;
	//释放环境句柄句柄
	ret = SQLFreeHandle(SQL_HANDLE_ENV, serverhenv);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
		cout << "free henv error!" << endl;
}

int main()
{
	msocketServer server(5099);
	cout << "网络初始化完成" << endl;

	mysqlInit();
	cout << "数据库初始化完成" << endl;

	while (true) {
		//等待客户请求到来
		cout << "等待客户连接" << endl;
		msocket *client = server.accept();//会阻塞进程，直到有客户端连接上来为止
		HANDLE hThread = CreateThread(NULL, 0, clientThread, (LPVOID)client, 0, NULL);
		if (hThread == NULL) //创建线程是否成功
			cout << "Create Thread Failed!" << endl;
	}
	server.close();
	mysqlClean();
	system("pause");
	return 0;
}
