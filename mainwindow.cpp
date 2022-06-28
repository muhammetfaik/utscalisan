#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sipclient.h>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sip->initialize_pjsua();

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_Reg_clicked()
{
    //sip->initialize_pjsua();
}

void MainWindow::on_Unreg_clicked()
{
    sip->unreg_pjsua();
}


void MainWindow::on_Call101_clicked()
{
    char callnumber[40]="sip:101@192.168.168.1";

    sip->make_call(callnumber);
}

void MainWindow::on_Call102_clicked()
{
    char callnumber[40]="sip:102@192.168.168.1";

    sip->make_call(callnumber);
}


void MainWindow::on_Call103_clicked()
{
    char callnumber[40]="sip:103@192.168.168.1";

    sip->make_call(callnumber);
}


void MainWindow::on_Hangup101_clicked()
{
    sip->hang_up();
}


void MainWindow::on_Hangup102_clicked()
{
    sip->hang_up();
}


void MainWindow::on_Hangup103_clicked()
{
    sip->hang_up();
}



void MainWindow::on_Answ_clicked()
{
    sip->answer();
}


void MainWindow::on_canc_clicked()
{
    sip->cancel();
}



