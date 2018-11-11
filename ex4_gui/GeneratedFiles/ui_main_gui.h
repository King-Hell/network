/********************************************************************************
** Form generated from reading UI file 'main_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_GUI_H
#define UI_MAIN_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_gui
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *flushDev;
    QPushButton *buttStart;
    QPushButton *buttStop;
    QPushButton *buttClear;
    QPushButton *buttFilter;
    QSplitter *splitter;
    QListWidget *devList;
    QTableWidget *packageList;
    QPushButton *buttScan;
    QMenuBar *menuBar;
    QMenu *menu123;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *main_gui)
    {
        if (main_gui->objectName().isEmpty())
            main_gui->setObjectName(QStringLiteral("main_gui"));
        main_gui->resize(1031, 597);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(main_gui->sizePolicy().hasHeightForWidth());
        main_gui->setSizePolicy(sizePolicy);
        main_gui->setMinimumSize(QSize(1031, 597));
        centralWidget = new QWidget(main_gui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(1031, 552));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 171, 31));
        flushDev = new QPushButton(centralWidget);
        flushDev->setObjectName(QStringLiteral("flushDev"));
        flushDev->setGeometry(QRect(180, 0, 171, 31));
        buttStart = new QPushButton(centralWidget);
        buttStart->setObjectName(QStringLiteral("buttStart"));
        buttStart->setGeometry(QRect(360, 0, 81, 31));
        buttStop = new QPushButton(centralWidget);
        buttStop->setObjectName(QStringLiteral("buttStop"));
        buttStop->setEnabled(false);
        buttStop->setGeometry(QRect(480, 0, 81, 31));
        buttStop->setCheckable(false);
        buttClear = new QPushButton(centralWidget);
        buttClear->setObjectName(QStringLiteral("buttClear"));
        buttClear->setGeometry(QRect(600, 0, 81, 31));
        buttFilter = new QPushButton(centralWidget);
        buttFilter->setObjectName(QStringLiteral("buttFilter"));
        buttFilter->setGeometry(QRect(730, 0, 81, 31));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(0, 30, 1031, 521));
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setMinimumSize(QSize(1031, 521));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(10);
        devList = new QListWidget(splitter);
        devList->setObjectName(QStringLiteral("devList"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(devList->sizePolicy().hasHeightForWidth());
        devList->setSizePolicy(sizePolicy1);
        devList->setMinimumSize(QSize(351, 0));
        QFont font;
        font.setPointSize(12);
        devList->setFont(font);
        splitter->addWidget(devList);
        packageList = new QTableWidget(splitter);
        if (packageList->columnCount() < 8)
            packageList->setColumnCount(8);
        if (packageList->rowCount() < 100)
            packageList->setRowCount(100);
        packageList->setObjectName(QStringLiteral("packageList"));
        sizePolicy.setHeightForWidth(packageList->sizePolicy().hasHeightForWidth());
        packageList->setSizePolicy(sizePolicy);
        packageList->setMinimumSize(QSize(671, 521));
        packageList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        packageList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        packageList->setDragEnabled(false);
        packageList->setDragDropOverwriteMode(true);
        packageList->setAlternatingRowColors(true);
        packageList->setSelectionMode(QAbstractItemView::SingleSelection);
        packageList->setSelectionBehavior(QAbstractItemView::SelectRows);
        packageList->setTextElideMode(Qt::ElideLeft);
        packageList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        packageList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        packageList->setSortingEnabled(true);
        packageList->setRowCount(100);
        packageList->setColumnCount(8);
        splitter->addWidget(packageList);
        packageList->horizontalHeader()->setCascadingSectionResizes(true);
        packageList->horizontalHeader()->setDefaultSectionSize(100);
        packageList->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        packageList->horizontalHeader()->setStretchLastSection(true);
        packageList->verticalHeader()->setVisible(false);
        buttScan = new QPushButton(centralWidget);
        buttScan->setObjectName(QStringLiteral("buttScan"));
        buttScan->setEnabled(false);
        buttScan->setGeometry(QRect(950, 0, 81, 31));
        main_gui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(main_gui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1031, 23));
        menu123 = new QMenu(menuBar);
        menu123->setObjectName(QStringLiteral("menu123"));
        main_gui->setMenuBar(menuBar);
        statusBar = new QStatusBar(main_gui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        main_gui->setStatusBar(statusBar);

        menuBar->addAction(menu123->menuAction());

        retranslateUi(main_gui);
        QObject::connect(flushDev, SIGNAL(clicked(bool)), main_gui, SLOT(flushDev()));
        QObject::connect(buttFilter, SIGNAL(clicked()), main_gui, SLOT(filter_show()));
        QObject::connect(buttStart, SIGNAL(clicked()), main_gui, SLOT(start()));
        QObject::connect(buttStop, SIGNAL(clicked()), main_gui, SLOT(stop()));
        QObject::connect(buttClear, SIGNAL(clicked()), main_gui, SLOT(clear()));
        QObject::connect(packageList, SIGNAL(cellDoubleClicked(int,int)), main_gui, SLOT(data_show(int,int)));
        QObject::connect(devList, SIGNAL(currentRowChanged(int)), main_gui, SLOT(start(int)));
        QObject::connect(buttScan, SIGNAL(clicked()), main_gui, SLOT(scan_show()));

        QMetaObject::connectSlotsByName(main_gui);
    } // setupUi

    void retranslateUi(QMainWindow *main_gui)
    {
        main_gui->setWindowTitle(QApplication::translate("main_gui", "\347\275\221\347\273\234\345\227\205\346\216\242\345\231\250", nullptr));
        label->setText(QApplication::translate("main_gui", "\347\275\221\347\273\234\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        flushDev->setText(QApplication::translate("main_gui", "\345\210\267\346\226\260\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        buttStart->setText(QApplication::translate("main_gui", "\345\274\200\345\247\213", nullptr));
        buttStop->setText(QApplication::translate("main_gui", "\345\201\234\346\255\242", nullptr));
        buttClear->setText(QApplication::translate("main_gui", "\346\270\205\347\251\272", nullptr));
        buttFilter->setText(QApplication::translate("main_gui", "\350\277\207\346\273\244", nullptr));
        buttScan->setText(QApplication::translate("main_gui", "\347\253\257\345\217\243\346\211\253\346\217\217", nullptr));
        menu123->setTitle(QApplication::translate("main_gui", "\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class main_gui: public Ui_main_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_GUI_H
