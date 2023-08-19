#include "login.h"
#include "ui_login.h"
#include "main_profile.h"
#include "mainwindow.h"

#include <QtDebug>

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_login_btn_clicked()
{
    main_profile *prof = nullptr;

    bool login_status = true;
    std::string username, password;
    username = ui->ln_username->text().toStdString();
    password = ui->ln_pass->text().toStdString();

    login_status = app.d1.login(app, username, password);

    if(login_status == true)
    {
        prof = new main_profile;
        prof->set_vars(app.get_users(), app.get_org(), app.get_ans(), app.get_hashtags(), username);
        prof->fill_out();
        prof->show();
        this->close();
    }
}

void login::on_btn_back_clicked()
{
    MainWindow *window = nullptr;
    window = new MainWindow;
    window->show();
    this->close();
}
