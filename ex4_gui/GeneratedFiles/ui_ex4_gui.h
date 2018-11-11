/********************************************************************************
** Form generated from reading UI file 'ex4_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EX4_GUI_H
#define UI_EX4_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ex4_guiClass
{
public:
    QWidget *centralWidget;
    QListWidget *devList;
    QLabel *label;
    QPushButton *flushDev;
    QListWidget *packageList;
    QPushButton *buttStart;
    QPushButton *buttStop;
    QPushButton *buttClear;
    QPushButton *buttClear_2;
    QMenuBar *menuBar;
    QMenu *menu123;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ex4_guiClass)
    {
        if (ex4_guiClass->objectName().isEmpty())
            ex4_guiClass->setObjectName(QStringLiteral("ex4_guiClass"));
        ex4_guiClass->resize(1024, 597);
        centralWidget = new QWidget(ex4_guiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        devList = new QListWidget(centralWidget);
        devList->setObjectName(QStringLiteral("devList"));
        devList->setGeometry(QRect(0, 30, 351, 521));
        QFont font;
        font.setPointSize(12);
        devList->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 171, 31));
        flushDev = new QPushButton(centralWidget);
        flushDev->setObjectName(QStringLiteral("flushDev"));
        flushDev->setGeometry(QRect(180, 0, 171, 31));
        packageList = new QListWidget(centralWidget);
        packageList->setObjectName(QStringLiteral("packageList"));
        packageList->setGeometry(QRect(360, 30, 671, 521));
        buttStart = new QPushButton(centralWidget);
        buttStart->setObjectName(QStringLiteral("buttStart"));
        buttStart->setGeometry(QRect(360, 0, 81, 31));
        buttStop = new QPushButton(centralWidget);
        buttStop->setObjectName(QStringLiteral("buttStop"));
        buttStop->setGeometry(QRect(480, 0, 81, 31));
        buttClear = new QPushButton(centralWidget);
        buttClear->setObjectName(QStringLiteral("buttClear"));
        buttClear->setGeometry(QRect(600, 0, 81, 31));
        buttClear_2 = new QPushButton(centralWidget);
        buttClear_2->setObjectName(QStringLiteral("buttClear_2"));
        buttClear_2->setGeometry(QRect(730, 0, 81, 31));
        ex4_guiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ex4_guiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 23));
        menu123 = new QMenu(menuBar);
        menu123->setObjectName(QStringLiteral("menu123"));
        ex4_guiClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(ex4_guiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ex4_guiClass->setStatusBar(statusBar);

        menuBar->addAction(menu123->menuAction());

        retranslateUi(ex4_guiClass);
        QObject::connect(flushDev, SIGNAL(clicked(bool)), ex4_guiClass, SLOT(flushDev()));
        QObject::connect(buttClear_2, SIGNAL(clicked()), ex4_guiClass, SLOT(filter_show()));

        QMetaObject::connectSlotsByName(ex4_guiClass);
    } // setupUi

    void retranslateUi(QMainWindow *ex4_guiClass)
    {
        ex4_guiClass->setWindowTitle(QApplication::translate("ex4_guiClass", "\347\275\221\347\273\234\345\227\205\346\216\242\345\231\250", nullptr));
        label->setText(QApplication::translate("ex4_guiClass", "\347\275\221\347\273\234\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        flushDev->setText(QApplication::translate("ex4_guiClass", "\345\210\267\346\226\260\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        buttStart->setText(QApplication::translate("ex4_guiClass", "\345\274\200\345\247\213", nullptr));
        buttStop->setText(QApplication::translate("ex4_guiClass", "\345\201\234\346\255\242", nullptr));
        buttClear->setText(QApplication::translate("ex4_guiClass", "\346\270\205\347\251\272", nullptr));
        buttClear_2->setText(QApplication::translate("ex4_guiClass", "\350\277\207\346\273\244", nullptr));
        menu123->setTitle(QApplication::translate("ex4_guiClass", "\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ex4_guiClass: public Ui_ex4_guiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EX4_GUI_H
