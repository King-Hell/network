#include"dataThread.h"

dataThread::dataThread(mpcap* mp) {
	runFlag = true;
	index = -1;
	this->mp = mp;
}

void dataThread::run()
{
	if (index == -1)
		return;
	if (runFlag == false)
		runFlag = true;
	QStringList info;
	info.append("");
	if (!mp->openDevice(index)) {
		info[0]=("Error");
		emit(updateList(info));
	}
	else
		while (runFlag&&info[0] != "Error") {
			info = mp->getData();
			if (info[0] == "")
				continue;
			emit updateList(info);
		}
}

void dataThread::stop()
{
	runFlag = false;
}

void dataThread::setIndex(int index) {
	this->index = index;
}
