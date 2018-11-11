/********************************************************************************
** Form generated from reading UI file 'scan_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCAN_GUI_H
#define UI_SCAN_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_scan_gui
{
public:
    QPlainTextEdit *plainTextEdit;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *scan_gui)
    {
        if (scan_gui->objectName().isEmpty())
            scan_gui->setObjectName(QStringLiteral("scan_gui"));
        scan_gui->resize(580, 386);
        plainTextEdit = new QPlainTextEdit(scan_gui);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 40, 581, 351));
        label = new QLabel(scan_gui);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 61, 41));
        lineEdit = new QLineEdit(scan_gui);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 0, 151, 41));
        pushButton = new QPushButton(scan_gui);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(340, 0, 101, 41));
        pushButton_2 = new QPushButton(scan_gui);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(470, 0, 81, 41));

        retranslateUi(scan_gui);
        QObject::connect(pushButton, SIGNAL(clicked()), scan_gui, SLOT(scan()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), scan_gui, SLOT(showOpen()));

        QMetaObject::connectSlotsByName(scan_gui);
    } // setupUi

    void retranslateUi(QWidget *scan_gui)
    {
        scan_gui->setWindowTitle(QApplication::translate("scan_gui", "\347\253\257\345\217\243\346\211\253\346\217\217", nullptr));
        label->setText(QApplication::translate("scan_gui", "\347\233\256\347\232\204\345\234\260\345\235\200", nullptr));
        lineEdit->setPlaceholderText(QApplication::translate("scan_gui", "Any Address", nullptr));
        pushButton->setText(QApplication::translate("scan_gui", "\346\211\253\346\217\217", nullptr));
        pushButton_2->setText(QApplication::translate("scan_gui", "\345\210\206\346\236\220\345\217\257\347\224\250\347\253\257\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class scan_gui: public Ui_scan_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCAN_GUI_H
