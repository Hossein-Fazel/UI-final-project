#include "others_profile.h"
#include "ui_others_profile.h"
#include "Base_User.hpp"

#include <QString>

others_profile::others_profile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::others_profile)
{
    ui->setupUi(this);
}

others_profile::~others_profile()
{
    delete ui;
}


void others_profile::fill_out(Base_User *user, std::string type)
{
    QPixmap pic_addr(QString::fromStdString(user->get_pic()));
    ui->lbl_pic->setPixmap(pic_addr.scaled(ui->lbl_pic->width(), ui->lbl_pic->height(), Qt::KeepAspectRatio));

    ui->ln_name->setText(QString::fromStdString(user->get_name()));
    ui->ln_username->setText(QString::fromStdString(user->get_username()));

    if(type == "ans")
    {
        ui->groupBox_2->setStyleSheet("background-color: gray;");
        ui->ln_country->setEnabled(false);
        ui->ln_follower->setEnabled(false);
        ui->ln_following->setText(QString::number(user->get_following_num()));
        ui->te_bio->setEnabled(false);
        ui->ln_link->setEnabled(false);
        ui->ln_manager->setEnabled(false);
        ui->ln_phone->setEnabled(false);
        ui->dt_birthday->setEnabled(false);
    }

    else if(type == "org")
    {
        QString style = "background-color: " + QString::fromStdString(user->get_header()) + ';';
        ui->groupBox_2->setStyleSheet(style);
        ui->ln_country->setText(QString::fromStdString(user->get_country()));
        ui->ln_follower->setText(QString::number(user->get_followers_num()));
        ui->ln_following->setEnabled(false);
        ui->te_bio->setText(QString::fromStdString(user->get_biography()));
        ui->ln_link->setText(QString::fromStdString(user->get_link()));
        ui->ln_phone->setText(QString::fromStdString(user->get_phone()));
        ui->dt_birthday->setEnabled(false);
    }

    else
    {
        QString style = "background-color: " + QString::fromStdString(user->get_header()) + ';';
        ui->groupBox_2->setStyleSheet(style);
        ui->ln_country->setText(QString::fromStdString(user->get_country()));
        ui->ln_follower->setText(QString::number(user->get_followers_num()));
        ui->ln_following->setText(QString::number(user->get_following_num()));
        ui->te_bio->setText(QString::fromStdString(user->get_biography()));
        ui->ln_link->setText(QString::fromStdString(user->get_link()));
        ui->ln_manager->setEnabled(false);
        ui->ln_phone->setText(QString::fromStdString(user->get_phone()));

        ui->dt_birthday->setDate(user->get_birthday());
    }
}
