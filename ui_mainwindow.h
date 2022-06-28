/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *Call101;
    QPushButton *Hangup101;
    QPushButton *Reg;
    QPushButton *Unreg;
    QPushButton *Answ;
    QPushButton *Call102;
    QPushButton *Hangup102;
    QPushButton *Call103;
    QPushButton *Hangup103;
    QPushButton *canc;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(546, 336);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Call101 = new QPushButton(centralwidget);
        Call101->setObjectName(QString::fromUtf8("Call101"));
        Call101->setGeometry(QRect(40, 110, 89, 25));
        Hangup101 = new QPushButton(centralwidget);
        Hangup101->setObjectName(QString::fromUtf8("Hangup101"));
        Hangup101->setGeometry(QRect(140, 110, 89, 25));
        Reg = new QPushButton(centralwidget);
        Reg->setObjectName(QString::fromUtf8("Reg"));
        Reg->setGeometry(QRect(40, 30, 89, 25));
        Unreg = new QPushButton(centralwidget);
        Unreg->setObjectName(QString::fromUtf8("Unreg"));
        Unreg->setGeometry(QRect(140, 30, 89, 25));
        Answ = new QPushButton(centralwidget);
        Answ->setObjectName(QString::fromUtf8("Answ"));
        Answ->setGeometry(QRect(300, 30, 89, 25));
        Call102 = new QPushButton(centralwidget);
        Call102->setObjectName(QString::fromUtf8("Call102"));
        Call102->setGeometry(QRect(40, 150, 89, 25));
        Hangup102 = new QPushButton(centralwidget);
        Hangup102->setObjectName(QString::fromUtf8("Hangup102"));
        Hangup102->setGeometry(QRect(140, 150, 89, 25));
        Call103 = new QPushButton(centralwidget);
        Call103->setObjectName(QString::fromUtf8("Call103"));
        Call103->setGeometry(QRect(40, 190, 89, 25));
        Hangup103 = new QPushButton(centralwidget);
        Hangup103->setObjectName(QString::fromUtf8("Hangup103"));
        Hangup103->setGeometry(QRect(140, 190, 89, 25));
        canc = new QPushButton(centralwidget);
        canc->setObjectName(QString::fromUtf8("canc"));
        canc->setGeometry(QRect(430, 30, 89, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 546, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        Call101->setText(QApplication::translate("MainWindow", "Call101", nullptr));
        Hangup101->setText(QApplication::translate("MainWindow", "HangUp101", nullptr));
        Reg->setText(QApplication::translate("MainWindow", "Register", nullptr));
        Unreg->setText(QApplication::translate("MainWindow", "Unreg", nullptr));
        Answ->setText(QApplication::translate("MainWindow", "Answer", nullptr));
        Call102->setText(QApplication::translate("MainWindow", "Call102", nullptr));
        Hangup102->setText(QApplication::translate("MainWindow", "HangUp102", nullptr));
        Call103->setText(QApplication::translate("MainWindow", "Call103", nullptr));
        Hangup103->setText(QApplication::translate("MainWindow", "HangUp103", nullptr));
        canc->setText(QApplication::translate("MainWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
