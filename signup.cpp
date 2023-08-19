#include "signup.h"
#include "ui_signup.h"
#include "main_profile.h"
#include "mainwindow.h"

#include <QMessageBox>

signup::signup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    ui->type->addItem("Personal User");
    ui->type->addItem("Organisation User");
    ui->type->addItem("Anonymous User");


}

signup::~signup()
{
    delete ui;
}


void signup::on_signup_btn_clicked()
{
    main_profile *prof;

    bool is_complete = true;
    std::string Ac_name = ui->ln_name->text().toStdString(),
            Ac_username = ui->ln_username->text().toStdString(),
            Ac_password = ui->ln_password->text().toStdString(),
            Ac_manager = ui->ln_manager->text().toStdString(),
            Ac_bio = ui->ln_bio->toPlainText().toStdString(),
            Ac_country = ui->ln_country->text().toStdString(),
            Ac_birth = ui->ln_birthday->text().toStdString(),
            Ac_phone = ui->ln_phone->text().toStdString(),
            Ac_link = ui->ln_link->text().toStdString(),
            Ac_color = ui->cm_header->currentText().toStdString();

    if(!Ac_username.empty() and !Ac_password.empty())
    {
        if(ui->type->currentText() == "Personal User")
        {
            if(Ac_name.empty())
            {
                QMessageBox msg;
                msg.setText("! Please enter your name");
                msg.exec();
            }

            else if(Ac_phone.empty())
            {
                QMessageBox msg;
                msg.setText("! Please enter your phone number.");
                msg.exec();
            }

            else
            {
                is_complete = app.d1.signup(app, Ac_name, Ac_username, Ac_password, Ac_bio, Ac_country, Ac_birth, Ac_phone, Ac_link, Ac_color);
                if(is_complete == true)
                {
                    bool login_status = true;
                    login_status = app.d1.login(app,Ac_username, Ac_password);
                    if(login_status == true)
                    {
                        app.put_users();
                        prof = new main_profile;
                        prof->set_vars(app.get_users(), app.get_org(), app.get_ans(), app.get_hashtags(), Ac_username);
                        prof->fill_out();
                        prof->show();
                        this->close();
                    }
                }
            }
        }
        else if(ui->type->currentText() == "Organisation User")
        {
            if(Ac_name.empty())
            {
                QMessageBox msg;
                msg.setText("! Please enter your name.");
                msg.exec();
            }

            else if(Ac_phone.empty())
            {
                QMessageBox msg;
                msg.setText("! Please enter your phone number.");
                msg.exec();
            }

            else
            {
                is_complete = app.d1.signupM(app,Ac_name,Ac_username,Ac_password,Ac_manager,Ac_bio,Ac_country,Ac_phone,Ac_link,Ac_color);
                if(is_complete == true)
                {
                    bool login_status = true;
                    login_status = app.d1.login(app,Ac_username, Ac_password);
                    if(login_status == true)
                    {
                        app.put_users();
                        prof = new main_profile;
                        prof->set_vars(app.get_users(), app.get_org(), app.get_ans(), app.get_hashtags(), Ac_username);
                        prof->fill_out();
                        prof->show();
                        this->close();
                    }
                }
            }
        }

        else if(ui->type->currentText() == "Anonymous User")
        {
            is_complete = app.d1.signup(app, Ac_username, Ac_password);
            if(is_complete == true)
            {
               bool login_status = true;
               login_status = app.d1.login(app,Ac_username, Ac_password);
               if(login_status == true)
               {
                   app.put_users();
                   prof = new main_profile;
                   prof->set_vars(app.get_users(), app.get_org(), app.get_ans(), app.get_hashtags(), Ac_username);
                   prof->fill_out();
                   prof->show();
                   this->close();
               }
            }
        }
    }

    else
    {
        QMessageBox msg;
        msg.setText("! The username and password can not be empty.");
        msg.exec();
    }
}


void signup::on_type_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Personal User")
    {
        ui->ln_username->setPlaceholderText("Required *");
        ui->ln_password->setPlaceholderText("Required *");
        ui->ln_phone->setPlaceholderText("Required *");
        ui->ln_manager->setPlaceholderText("");

        ui->ln_name->setEnabled(true);
        ui->ln_name->clear();
        ui->ln_name->setPlaceholderText("Required *");
        ui->ln_bio->setEnabled(true);
        ui->ln_country->setEnabled(true);
        ui->cm_header->setEnabled(true);
        ui->cm_header->setCurrentText("white");
        ui->ln_birthday->setEnabled(true);
        ui->ln_phone->setEnabled(true);
        ui->ln_manager->setEnabled(false);
        ui->ln_link->setEnabled(true);
    }

    else if (arg1 == "Organisation User")
    {
        ui->ln_username->setPlaceholderText("Required *");
        ui->ln_password->setPlaceholderText("Required *");
        ui->ln_phone->setPlaceholderText("Required *");
        ui->ln_manager->setPlaceholderText("Required *");

        ui->ln_name->setEnabled(true);
        ui->ln_name->clear();
        ui->ln_name->setPlaceholderText("Required *");
        ui->ln_bio->setEnabled(true);
        ui->ln_country->setEnabled(true);
        ui->cm_header->setEnabled(true);
        ui->cm_header->setCurrentText("white");
        ui->ln_birthday->setEnabled(false);
        ui->ln_phone->setEnabled(true);
        ui->ln_manager->setEnabled(true);
        ui->ln_link->setEnabled(true);
    }

    else if(arg1 == "Anonymous User")
    {
        ui->ln_username->setPlaceholderText("Required *");
        ui->ln_password->setPlaceholderText("Required *");
        ui->ln_phone->setPlaceholderText("");
        ui->ln_manager->setPlaceholderText("");

        ui->ln_name->setEnabled(false);
        ui->ln_name->setText("Anonymous User");
        ui->ln_bio->setEnabled(false);
        ui->ln_country->setEnabled(false);
        ui->cm_header->setEnabled(false);
        ui->cm_header->setCurrentText("gray");
        ui->ln_birthday->setEnabled(false);
        ui->ln_phone->setEnabled(false);
        ui->ln_manager->setEnabled(false);
        ui->ln_link->setEnabled(false);
    }
}

void signup::on_btn_back_clicked()
{
    MainWindow *window = nullptr;
    window = new MainWindow;
    window->show();
    this->close();
}

