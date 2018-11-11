/********************************************************************************
** Form generated from reading UI file 'filter_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTER_GUI_H
#define UI_FILTER_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_filter_gui
{
public:
    QCheckBox *checkBox_sip;
    QCheckBox *checkBox_dip;
    QCheckBox *checkBox_port;
    QCheckBox *checkBox_protocal;
    QLineEdit *lineEdit_sip;
    QLineEdit *lineEdit_dip;
    QLineEdit *lineEdit_port;
    QLineEdit *lineEdit_protocal;
    QPushButton *pushButton;

    void setupUi(QWidget *filter_gui)
    {
        if (filter_gui->objectName().isEmpty())
            filter_gui->setObjectName(QStringLiteral("filter_gui"));
        filter_gui->resize(396, 223);
        checkBox_sip = new QCheckBox(filter_gui);
        checkBox_sip->setObjectName(QStringLiteral("checkBox_sip"));
        checkBox_sip->setGeometry(QRect(40, 50, 71, 16));
        checkBox_dip = new QCheckBox(filter_gui);
        checkBox_dip->setObjectName(QStringLiteral("checkBox_dip"));
        checkBox_dip->setGeometry(QRect(40, 80, 71, 16));
        checkBox_port = new QCheckBox(filter_gui);
        checkBox_port->setObjectName(QStringLiteral("checkBox_port"));
        checkBox_port->setGeometry(QRect(40, 110, 71, 16));
        checkBox_protocal = new QCheckBox(filter_gui);
        checkBox_protocal->setObjectName(QStringLiteral("checkBox_protocal"));
        checkBox_protocal->setGeometry(QRect(40, 140, 71, 16));
        checkBox_protocal->setChecked(true);
        lineEdit_sip = new QLineEdit(filter_gui);
        lineEdit_sip->setObjectName(QStringLiteral("lineEdit_sip"));
        lineEdit_sip->setGeometry(QRect(120, 40, 171, 31));
        lineEdit_dip = new QLineEdit(filter_gui);
        lineEdit_dip->setObjectName(QStringLiteral("lineEdit_dip"));
        lineEdit_dip->setGeometry(QRect(120, 70, 171, 31));
        lineEdit_port = new QLineEdit(filter_gui);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(120, 100, 171, 31));
        lineEdit_protocal = new QLineEdit(filter_gui);
        lineEdit_protocal->setObjectName(QStringLiteral("lineEdit_protocal"));
        lineEdit_protocal->setGeometry(QRect(120, 130, 171, 31));
        pushButton = new QPushButton(filter_gui);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 170, 101, 41));

        retranslateUi(filter_gui);
        QObject::connect(pushButton, SIGNAL(clicked()), filter_gui, SLOT(setFilter()));

        QMetaObject::connectSlotsByName(filter_gui);
    } // setupUi

    void retranslateUi(QWidget *filter_gui)
    {
        filter_gui->setWindowTitle(QApplication::translate("filter_gui", "\350\277\207\346\273\244\345\231\250", nullptr));
        checkBox_sip->setText(QApplication::translate("filter_gui", "\346\272\220\345\234\260\345\235\200", nullptr));
        checkBox_dip->setText(QApplication::translate("filter_gui", "\347\233\256\347\232\204\345\234\260\345\235\200", nullptr));
        checkBox_port->setText(QApplication::translate("filter_gui", "\347\253\257\345\217\243", nullptr));
        checkBox_protocal->setText(QApplication::translate("filter_gui", "\345\215\217\350\256\256", nullptr));
        lineEdit_sip->setPlaceholderText(QApplication::translate("filter_gui", "Any Address", nullptr));
        lineEdit_dip->setPlaceholderText(QApplication::translate("filter_gui", "Any Address", nullptr));
        lineEdit_port->setPlaceholderText(QApplication::translate("filter_gui", "Any Protocal", nullptr));
        lineEdit_protocal->setText(QApplication::translate("filter_gui", "tcp or udp", nullptr));
        pushButton->setText(QApplication::translate("filter_gui", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class filter_gui: public Ui_filter_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTER_GUI_H
