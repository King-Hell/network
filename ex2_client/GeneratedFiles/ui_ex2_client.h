/********************************************************************************
** Form generated from reading UI file 'ex2_client.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EX2_CLIENT_H
#define UI_EX2_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ex2_clientClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QListView *listView;
    QPushButton *pushButton;

    void setupUi(QMainWindow *ex2_clientClass)
    {
        if (ex2_clientClass->objectName().isEmpty())
            ex2_clientClass->setObjectName(QStringLiteral("ex2_clientClass"));
        ex2_clientClass->resize(300, 666);
        centralWidget = new QWidget(ex2_clientClass);
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
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(0, 70, 300, 541));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(0, 610, 300, 61));
        pushButton->setFont(font);
        ex2_clientClass->setCentralWidget(centralWidget);

        retranslateUi(ex2_clientClass);

        QMetaObject::connectSlotsByName(ex2_clientClass);
    } // setupUi

    void retranslateUi(QMainWindow *ex2_clientClass)
    {
        ex2_clientClass->setWindowTitle(QApplication::translate("ex2_clientClass", "\344\270\273\347\225\214\351\235\242", nullptr));
        label->setText(QApplication::translate("ex2_clientClass", "\345\275\223\345\211\215\345\234\250\347\272\277\347\224\250\346\210\267", nullptr));
        pushButton->setText(QApplication::translate("ex2_clientClass", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ex2_clientClass: public Ui_ex2_clientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EX2_CLIENT_H
