#include "main_gui.h"

main_gui::main_gui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	filter = new filter_gui(&mp);
	filter->setWindowFlags(filter->windowFlags()&~Qt::WindowMinMaxButtonsHint);
	thread = new dataThread(&mp);
	connect(thread, &dataThread::updateList, this, &main_gui::getData);
	//�����б�
	QStringList header;
	header.append("ʱ��");
	header.append("Э��");
	header.append("Դ��ַ");
	header.append("Դ�˿�");
	header.append("Ŀ�ĵ�ַ");
	header.append("Ŀ�Ķ˿�");
	header.append("���ݰ�����");
	ui.packageList->setHorizontalHeaderLabels(header);
	ui.packageList->horizontalHeader()->resizeSection(0, 70);
	ui.packageList->horizontalHeader()->resizeSection(1, 50);
	ui.packageList->horizontalHeader()->resizeSection(2, 120);
	ui.packageList->horizontalHeader()->resizeSection(3, 70);
	ui.packageList->horizontalHeader()->resizeSection(4, 120);
	ui.packageList->horizontalHeader()->resizeSection(5, 70);
	ui.packageList->horizontalHeader()->hideSection(7);
	rowNum = 0;
	totalNum = 100;
}

void main_gui::flushDev() {
	//ˢ���豸�б� 
	ui.devList->clear();
	mp.clear();
	ui.devList->addItems(mp.getDevices());
}

void main_gui::filter_show() {
	filter->show();
}

void main_gui::start(int index)
{
	if (index == -1)
		QMessageBox::critical(NULL, "����", "��ѡ��һ�������豸");
	else {
		ui.buttStart->setEnabled(false);
		ui.buttStop->setEnabled(true);
		ui.buttScan->setEnabled(true);
		thread->setIndex(index);
		thread->start();
	}
		
}

void main_gui::start()
{
	start(ui.devList->currentRow());
}

void main_gui::stop()
{
	ui.buttStop->setEnabled(false);
	ui.buttStart->setEnabled(true);
	thread->stop();
}

void main_gui::clear()
{
	ui.packageList->clearContents();
	rowNum = 0;
	ui.packageList->scrollToTop();
	mp.clearData();
}

void main_gui::getData(QStringList info)
{
	for (int i = 0; i <8; i++) {
		QTableWidgetItem *item = new QTableWidgetItem(info[i]);
		ui.packageList->setItem(rowNum, i, item);
	}
	rowNum++;
	if (rowNum == totalNum)
		resizeTable();
}

void main_gui::closeEvent(QCloseEvent * event)
{
	mp.freeAllDevices();
	filter->close();
}

void main_gui::resizeTable()
{
	if (totalNum == 100000) {
		clear();
		totalNum = 0;
		ui.packageList->setRowCount(100);
	}
	ui.packageList->setRowCount(totalNum * 2);
	totalNum *= 2;
}

void main_gui::data_show(int x, int y)
{
	if (ui.packageList->item(x, 7)==NULL)
		return;
	mdata *da = mp.getData(ui.packageList->item(x, 7)->text().toInt());
	if (da == NULL)
		return;
	data_gui *mdata = new data_gui(da->length,da->content);
	mdata->setAttribute(Qt::WA_DeleteOnClose, true);
	mdata->show();
}

void main_gui::scan_show()
{
	scan_gui *scan = new scan_gui(&mp);
	scan->setAttribute(Qt::WA_DeleteOnClose, true);
	scan->show();
}
