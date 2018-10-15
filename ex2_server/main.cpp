#include"msocketServer.h"
#include<windows.h>
#include<sql.h>
#include <sqlext.h>
#include<map>
#include<vector>
#include<string>

map<string, msocket*> userList;//�û��б�

SQLHENV serverhenv;
SQLHDBC serverhdbc;
SQLHSTMT serverhstmt;
SQLRETURN ret;
SQLLEN length;

std::vector<std::string> split(std::string &str, std::string &pattern) {
	//�ָ��ַ�������
	std::vector<std::string> resVec;
	if ("" == str)
		return resVec;
	//�����ȡ���һ������
	size_t pos = str.find(pattern);
	size_t size = str.size();
	std::string x = str.substr(0, pos);
	resVec.push_back(x);
	str = str.substr(pos + 1, size);
	resVec.push_back(str);
	return resVec;
}
bool checkUser(const char *name, const char *pass) {
	//��ѯ�û���������
	SQLCHAR password[255];
	string select = "select password from user where username='" + (string)name + "';";
	//����ִ�������
	ret = SQLAllocHandle(SQL_HANDLE_STMT, serverhdbc, &serverhstmt);
	//ִ��SQL���
	ret = SQLExecDirect(serverhstmt, (SQLCHAR*)select.c_str(), SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		//������
		SQLBindCol(serverhstmt, 1, SQL_C_CHAR, (void*)password, sizeof(password), &length);
		//������ƶ�������,�������������
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
	cout << ip << ":������" << endl;
	string user = "";
	try {
		while (true) {
			//ת����Ϣ
			string message = sock->recv();
			string pattern = ":";
			vector<string> str = split(message, pattern);
			string ins = str[0];
			string content = str[1];
			cout << "����" << ins << "����" << content << endl;
			if (ins == "LOGIN") {
				//�����¼
				const char *username = NULL, *password;
				string pattern = ",";
				vector<string> info = split(content, pattern);
				username = info[0].c_str();//�û���
				password = info[1].c_str();//����
				user = username;
				if (checkUser(username, password)) {
					sock->send(string("SUCCESS"));
					for (auto i = userList.begin(); i != userList.end(); i++) 
							(*i).second->send("INFO:LOGIN;" + user);//�����пͻ���ˢ���û��б�
					userList.insert(pair<string, msocket*>(username, sock));
					cout << ip << ":�ѵ�¼,�û���:" << username << endl;
				}
				else {
					sock->send(string("FAILURE"));
					cout << ip << ":�ܾ�����,�û���:" << username << endl;
					break;
				}
			}
			else if (ins == "LIST") {
				//�����û��б�
				message = "";
				for (auto i = userList.begin(); i != userList.end(); i++)
					message += (*i).first + ",";
				sock->send(message);
				cout << ip << "�����û��б�" << endl;
			}
			else if (ins == "CHAT") {
				//��������
				string pattern = ";";
				vector<string> info = split(content, pattern);
				string chatTo = info[0];
				string chatContent = info[1];
				if (userList.find(chatTo) != userList.end()) {
					//Ҫ����Ķ�������
					msocket *chatSocket = userList.find(chatTo)->second;
					chatSocket->send("CHAT:" + user + ";" + chatContent + "\n");
				}
				else {
					//Ҫ����Ķ�������
					sock->send("CHAT:system;" + chatTo + "������\n");
				}
			}
			else if (ins == "LOGOUT") {
				//�����˳�
				userList.erase(user);
				for (auto i = userList.begin(); i != userList.end(); i++)
					(*i).second->send("INFO:LOGOUT;" + user);//�����пͻ���ˢ���û��б�
				cout << ip << user << "�˳�" << endl;
				break;
			}
		}
		sock->close();
		return 0;
	}
	catch (exception) {
		sock->close();
		cout << ip << "�쳣�˳�" << endl;
		if (user != "" && userList.find(user) != userList.end()) {
			userList.erase(user);
			for (auto i = userList.begin(); i != userList.end(); i++)
				(*i).second->send("INFO:LOGOUT;" + user);//�����пͻ���ˢ���û��б�
		}
		return -1;
	}

}

void mysqlInit() {

	//���价�����
	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &serverhenv);
	//���û�������
	ret = SQLSetEnvAttr(serverhenv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (!SQL_SUCCEEDED(ret)) {
		cout << "AllocEnvHandle error!" << endl;
		return;
	}
	//�������Ӿ��
	ret = SQLAllocHandle(SQL_HANDLE_DBC, serverhenv, &serverhdbc);
	if (!SQL_SUCCEEDED(ret)) {
		cout << "AllocDbcHandle error!" << endl;
		return;
	}
	//���ݿ�����
	ret = SQLConnect(serverhdbc, (SQLCHAR*)"network_ex2", SQL_NTS, (SQLCHAR*)"network", SQL_NTS, (SQLCHAR*)"1234", SQL_NTS);//�ڶ���������֮ǰ���õ�����Դ�����������ݿ��û���������
	if (!SQL_SUCCEEDED(ret)) {
		cout << "SQL_Connect error!" << endl;
		return;
	}
}
void mysqlClean() {
	//�ͷ������
	ret = SQLFreeHandle(SQL_HANDLE_STMT, serverhstmt);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
		cout << "free hstmt error!" << endl;
	//�Ͽ����ݿ�����
	ret = SQLDisconnect(serverhdbc);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
		cout << "disconnected error!" << endl;
	//�ͷ����Ӿ��
	ret = SQLFreeHandle(SQL_HANDLE_DBC, serverhdbc);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
		cout << "free hdbc error!" << endl;
	//�ͷŻ���������
	ret = SQLFreeHandle(SQL_HANDLE_ENV, serverhenv);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
		cout << "free henv error!" << endl;
}

int main()
{
	msocketServer server(5099);
	cout << "�����ʼ�����" << endl;

	mysqlInit();
	cout << "���ݿ��ʼ�����" << endl;

	while (true) {
		//�ȴ��ͻ�������
		cout << "�ȴ��ͻ�����" << endl;
		msocket *client = server.accept();//���������̣�ֱ���пͻ�����������Ϊֹ
		HANDLE hThread = CreateThread(NULL, 0, clientThread, (LPVOID)client, 0, NULL);
		if (hThread == NULL) //�����߳��Ƿ�ɹ�
			cout << "Create Thread Failed!" << endl;
	}
	server.close();
	mysqlClean();
	system("pause");
	return 0;
}
