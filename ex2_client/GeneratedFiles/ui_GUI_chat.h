/********************************************************************************
** Form generated from reading UI file 'GUI_chat.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_CHAT_H
#define UI_GUI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_chat
{
public:
    QTextBrowser *textBrowser;
    QPushButton *butt_send;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *GUI_chat)
    {
        if (GUI_chat->objectName().isEmpty())
            GUI_chat->setObjectName(QStringLiteral("GUI_chat"));
        GUI_chat->resize(666, 500);
        textBrowser = new QTextBrowser(GUI_chat);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(0, 0, 666, 381));
        butt_send = new QPushButton(GUI_chat);
        butt_send->setObjectName(QStringLiteral("butt_send"));
        butt_send->setGeometry(QRect(560, 390, 111, 111));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        butt_send->setFont(font);
        plainTextEdit = new QPlainTextEdit(GUI_chat);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 390, 561, 111));

        retranslateUi(GUI_chat);
        QObject::connect(butt_send, SIGNAL(clicked()), GUI_chat, SLOT(sendMessage()));

        QMetaObject::connectSlotsByName(GUI_chat);
    } // setupUi

    void retranslateUi(QWidget *GUI_chat)
    {
        GUI_chat->setWindowTitle(QApplication::translate("GUI_chat", "\350\201\212\345\244\251", nullptr));
        butt_send->setText(QApplication::translate("GUI_chat", "\345\217\221\351\200\201", nullptr));
        plainTextEdit->setPlaceholderText(QApplication::translate("GUI_chat", "\347\202\271\345\207\273\350\276\223\345\205\245\346\226\207\346\234\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_chat: public Ui_GUI_chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_CHAT_H
