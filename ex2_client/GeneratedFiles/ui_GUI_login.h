/********************************************************************************
** Form generated from reading UI file 'GUI_login.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_LOGIN_H
#define UI_GUI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_login
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *edit_username;
    QLineEdit *edit_password;
    QPushButton *pushButton;

    void setupUi(QWidget *GUI_login)
    {
        if (GUI_login->objectName().isEmpty())
            GUI_login->setObjectName(QStringLiteral("GUI_login"));
        GUI_login->resize(400, 300);
        label = new QLabel(GUI_login);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 80, 101, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(GUI_login);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 130, 101, 51));
        label_2->setFont(font);
        edit_username = new QLineEdit(GUI_login);
        edit_username->setObjectName(QStringLiteral("edit_username"));
        edit_username->setGeometry(QRect(160, 90, 211, 41));
        QFont font1;
        font1.setPointSize(20);
        edit_username->setFont(font1);
        edit_password = new QLineEdit(GUI_login);
        edit_password->setObjectName(QStringLiteral("edit_password"));
        edit_password->setGeometry(QRect(160, 140, 211, 41));
        QFont font2;
        font2.setPointSize(18);
        edit_password->setFont(font2);
        edit_password->setEchoMode(QLineEdit::Password);
        pushButton = new QPushButton(GUI_login);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(130, 210, 121, 51));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(20);
        font3.setBold(false);
        font3.setWeight(50);
        pushButton->setFont(font3);

        retranslateUi(GUI_login);
        QObject::connect(pushButton, SIGNAL(clicked()), GUI_login, SLOT(login()));

        QMetaObject::connectSlotsByName(GUI_login);
    } // setupUi

    void retranslateUi(QWidget *GUI_login)
    {
        GUI_login->setWindowTitle(QApplication::translate("GUI_login", "\347\231\273\345\275\225", nullptr));
        label->setText(QApplication::translate("GUI_login", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QApplication::translate("GUI_login", "\345\257\206\347\240\201", nullptr));
        pushButton->setText(QApplication::translate("GUI_login", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_login: public Ui_GUI_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_LOGIN_H
