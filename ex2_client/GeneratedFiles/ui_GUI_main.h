/********************************************************************************
** Form generated from reading UI file 'GUI_main.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_MAIN_H
#define UI_GUI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_main
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_user;
    QListWidget *userListWidget;
    QLabel *label_2;

    void setupUi(QMainWindow *GUI_main)
    {
        if (GUI_main->objectName().isEmpty())
            GUI_main->setObjectName(QStringLiteral("GUI_main"));
        GUI_main->resize(300, 666);
        centralWidget = new QWidget(GUI_main);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 300, 71));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(0, 610, 300, 61));
        pushButton->setFont(font);
        label_user = new QLabel(centralWidget);
        label_user->setObjectName(QStringLiteral("label_user"));
        label_user->setGeometry(QRect(0, 60, 301, 20));
        userListWidget = new QListWidget(centralWidget);
        userListWidget->setObjectName(QStringLiteral("userListWidget"));
        userListWidget->setGeometry(QRect(-1, 100, 601, 511));
        QFont font1;
        font1.setPointSize(28);
        userListWidget->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 80, 301, 16));
        label_2->setAlignment(Qt::AlignCenter);
        GUI_main->setCentralWidget(centralWidget);

        retranslateUi(GUI_main);
        QObject::connect(userListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), GUI_main, SLOT(beginChat(QListWidgetItem*)));
        QObject::connect(pushButton, SIGNAL(clicked()), GUI_main, SLOT(close()));

        QMetaObject::connectSlotsByName(GUI_main);
    } // setupUi

    void retranslateUi(QMainWindow *GUI_main)
    {
        GUI_main->setWindowTitle(QApplication::translate("GUI_main", "\344\270\273\347\225\214\351\235\242", nullptr));
        label->setText(QApplication::translate("GUI_main", "\345\275\223\345\211\215\345\234\250\347\272\277\347\224\250\346\210\267", nullptr));
        pushButton->setText(QApplication::translate("GUI_main", "\351\200\200\345\207\272", nullptr));
        label_user->setText(QApplication::translate("GUI_main", "\346\210\221\347\232\204\347\224\250\346\210\267\345\220\215    IP\345\234\260\345\235\200", nullptr));
        label_2->setText(QApplication::translate("GUI_main", "\345\217\214\345\207\273\351\200\211\346\213\251\350\246\201\350\201\212\345\244\251\347\232\204\347\224\250\346\210\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_main: public Ui_GUI_main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_MAIN_H
