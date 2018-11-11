/********************************************************************************
** Form generated from reading UI file 'data_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATA_GUI_H
#define UI_DATA_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_data_gui
{
public:
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *data_gui)
    {
        if (data_gui->objectName().isEmpty())
            data_gui->setObjectName(QStringLiteral("data_gui"));
        data_gui->resize(667, 440);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(data_gui->sizePolicy().hasHeightForWidth());
        data_gui->setSizePolicy(sizePolicy);
        data_gui->setMinimumSize(QSize(667, 440));
        horizontalLayout = new QHBoxLayout(data_gui);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new QPlainTextEdit(data_gui);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        horizontalLayout->addWidget(plainTextEdit);


        retranslateUi(data_gui);

        QMetaObject::connectSlotsByName(data_gui);
    } // setupUi

    void retranslateUi(QWidget *data_gui)
    {
        data_gui->setWindowTitle(QApplication::translate("data_gui", "\346\225\260\346\215\256\345\214\205\345\206\205\345\256\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class data_gui: public Ui_data_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATA_GUI_H
