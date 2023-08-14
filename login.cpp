#include "login.h"
#include "ui_login.h"

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
    std::string username, password;
    username = ui->ln_username->text().toStdString();
    password = ui->ln_pass->text().toStdString();

    app.d1.login(app, username, password);
}

