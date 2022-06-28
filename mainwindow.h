#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sipclient.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Call101_clicked();

    void on_Reg_clicked();

    void on_Hangup101_clicked();

    void on_Hangup102_clicked();

    void on_Hangup103_clicked();

    void on_Call102_clicked();

    void on_Call103_clicked();

    void on_Answ_clicked();

    void on_canc_clicked();

    void on_Unreg_clicked();

private:

    Ui::MainWindow *ui;
    sipclient *sip;
};
#endif // MAINWINDOW_H
