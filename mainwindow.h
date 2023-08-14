#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Twitterak_Class.hpp"

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
    void on_exit_btn_clicked();

    void on_login_btn_clicked();

    void on_signup_btn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
