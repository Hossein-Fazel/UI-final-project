#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "signup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_btn_clicked()
{
    exit(0);
}
void MainWindow::on_login_btn_clicked()
{
    login *login_page = nullptr;
    login_page = new login;

    login_page->show();
}

void MainWindow::on_signup_btn_clicked()
{
    signup *signup_page = nullptr;
    signup_page = new signup;
    signup_page->show();
}
