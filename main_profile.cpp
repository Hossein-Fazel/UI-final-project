#include "main_profile.h"
#include "ui_main_profile.h"

#include <QMessageBox>
#include <Qstring>
#include <QString>
#include <fstream>

main_profile::main_profile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_profile)
{
    ui->setupUi(this);

//    ====================================== set additional settings =============================================
    change_ro(1);
    ui->ln_pass->hide();
    ui->lb_pass->hide();
    ui->btn_discard->hide();
    ui->btn_save->hide();
    ui->lb_header->hide();
    ui->ln_header->hide();
}

main_profile::~main_profile()
{
    delete ui;
}

void main_profile::fill_out()
{
    if(li_user->get_name() == "Anonymous User")
    {
        ui->ln_name->setText(QString::fromStdString(li_user->get_name()));
        ui->ln_username->setText(QString::fromStdString(li_user->get_username()));

        ui->ln_manager->setEnabled(false);
        ui->ln_phone->setEnabled(false);
        ui->ln_country->setEnabled(false);
        ui->ln_link->setEnabled(false);
        ui->te_bio->setEnabled(false);
        ui->dt_birthday->setEnabled(false);
        ui->ln_header->setEnabled(false);
        ui->ln_follower->setEnabled(false);
        ui->ln_following->setText(QString::number(li_user->get_following_num()));

        ui->ln_pass->setText(QString::fromStdString(li_user->get_password()));
    }

    else
    {
        ui->ln_name->setText(QString::fromStdString(li_user->get_name()));
        ui->ln_username->setText(QString::fromStdString(li_user->get_username()));

        if(org_user.count(li_user->get_username()) == 1)
        {
            ui->dt_birthday->setEnabled(false);
            ui->ln_manager->setEnabled(true);
            ui->ln_manager->setReadOnly(true);
            ui->ln_follower->setText(QString::number(li_user->get_followers_num()));
            ui->ln_following->setEnabled(false);
        }

        else
        {
            int year = std::stoi(li_user->get_birthday().substr(0,4));
            int month = std::stoi(li_user->get_birthday().substr(5, 6));
            int day = std::stoi(li_user->get_birthday().substr(8, 9));

            QDate date;
            date.setDate(year,month,day);
            ui->dt_birthday->setDate(date);

            ui->ln_manager->setEnabled(false);
            ui->ln_follower->setText(QString::number(li_user->get_followers_num()));
            ui->ln_following->setText(QString::number(li_user->get_followers_num()));
        }

        ui->ln_phone->setText(QString::fromStdString(li_user->get_phone()));
        ui->ln_country->setText(QString::fromStdString(li_user->get_country()));
        ui->ln_link->setText(QString::fromStdString(li_user->get_link()));
        ui->te_bio->setText(QString::fromStdString(li_user->get_biography()));
        ui->ln_pass->setText(QString::fromStdString(li_user->get_password()));
        ui->ln_header->setText(QString::fromStdString(li_user->get_header()));
    }
}


void main_profile::fill_out_old()
{
    if(li_user->get_name() == "Anonymous User")
    {
        ui->ln_name->setText(QString::fromStdString(old_user.name));
        ui->ln_username->setText(QString::fromStdString(old_user.username));

        ui->ln_manager->setEnabled(false);
        ui->ln_phone->setEnabled(false);
        ui->ln_country->setEnabled(false);
        ui->ln_link->setEnabled(false);
        ui->te_bio->setEnabled(false);
        ui->dt_birthday->setEnabled(false);
        ui->ln_header->setEnabled(false);

        ui->ln_pass->setText(QString::fromStdString(old_user.pass));
    }

    else
    {
        ui->ln_name->setText(QString::fromStdString(old_user.name));
        ui->ln_username->setText(QString::fromStdString(old_user.username));

        if(org_user.count(li_user->get_username()) == 1)
        {
            ui->dt_birthday->setEnabled(false);
        }

        else
        {
            int year = std::stoi(old_user.birth.substr(0,4));
            int month = std::stoi(old_user.birth.substr(4, 6));
            int day = std::stoi(old_user.birth.substr(8,9));

            QDate date;
            date.setDate(year,month,day);
            ui->dt_birthday->setDate(date);

            ui->ln_manager->setEnabled(false);
        }

        ui->ln_phone->setText(QString::fromStdString(old_user.phone));
        ui->ln_country->setText(QString::fromStdString(old_user.country));
        ui->ln_link->setText(QString::fromStdString(old_user.link));
        ui->te_bio->setText(QString::fromStdString(old_user.bio));
        ui->ln_pass->setText(QString::fromStdString(old_user.pass));
        ui->ln_header->setText(QString::fromStdString(old_user.header));
    }
}

void main_profile::push_hashtag(std::string hashtag, tweet tw)
{
    Hashtags[hashtag].push_back(tw);
}

void main_profile::put_users()
{
    std::ofstream wuser;
    wuser.open("users.txt");

    for(auto i : users)
    {
        wuser << "type:user" << std::endl;
        wuser << "name:" << i.second.get_name() << std::endl;
        wuser << "username:" << i.second.get_username() << std::endl;
        wuser << "bio:" << i.second.get_biography() << std::endl;
        wuser << "link:" << i.second.get_link() << std::endl;
        wuser << "phone:" << i.second.get_phone() << std::endl;
        wuser << "header:" << i.second.get_header() << std::endl;
        wuser << "country:" << i.second.get_country() << std::endl;
        wuser << "birthday:" << i.second.get_birthday() << std::endl;
        wuser << "password:" << i.second.get_password() << std::endl;
        wuser << "last_num:" << i.second.get_last_number() << std::endl;

        wuser << "followers:";
        for(auto j : i.second.get_followers())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "followings:";
        for(auto j : i.second.get_following())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "passwords:";
        for(auto j : i.second.get_passwords())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;


        wuser << "my_mentions:" << std::endl;
        if(i.second.get_mention_trs().size() != 0)
        {
            for(auto j : i.second.get_mention_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "tweet_likes:" << std::endl;

        if(i.second.get_tweetlike_trs().size() != 0)
        {
            for(auto j : i.second.get_tweetlike_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "***" << std::endl;
        i.second.search_to_file();
    }

    for (auto i : org_user)
    {
        wuser << "type:org" << std::endl;
        wuser << "name:" << i.second.get_name() << std::endl;
        wuser << "username:" << i.second.get_username() << std::endl;
        wuser << "bio:" << i.second.get_biography() << std::endl;
        wuser << "link:" << i.second.get_link() << std::endl;
        wuser << "phone:" << i.second.get_phone() << std::endl;
        wuser << "header:" << i.second.get_header() << std::endl;
        wuser << "country:" << i.second.get_country() << std::endl;
        wuser << "password:" << i.second.get_password() << std::endl;
        wuser << "last_num:" << i.second.get_last_number() << std::endl;
//        wuser << "manager:" << i.second.get_manager_username() << std::endl;
        wuser << "followers:";
        for(auto j : i.second.get_followers())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "followings:";
        for(auto j : i.second.get_following())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "passwords:";
        for(auto j : i.second.get_passwords())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;


        wuser << "my_mentions:" << std::endl;
        if(i.second.get_mention_trs().size() != 0)
        {
            for(auto j : i.second.get_mention_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "tweet_likes:" << std::endl;
        if(i.second.get_tweetlike_trs().size() != 0)
        {
            for(auto j : i.second.get_tweetlike_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "***" << std::endl;
        i.second.search_to_file();
    }

    for (auto i : ans_user)
    {
        wuser << "type:ans" << std::endl;
        wuser << "username:" << i.second.get_username() << std::endl;
        wuser << "password:" << i.second.get_password() << std::endl;

        wuser << "followings:";
        for(auto j : i.second.get_following())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "passwords:";
        for(auto j : i.second.get_passwords())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "my_mentions:" << std::endl;
        if(i.second.get_mention_trs().size() != 0)
        {
            for(auto j : i.second.get_mention_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "tweet_likes:" << std::endl;
        if(i.second.get_tweetlike_trs().size() != 0)
        {
            for(auto j : i.second.get_tweetlike_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "***" << std::endl;
    }

    wuser.close();
}

void main_profile::set_vars(std::unordered_map<std::string, user> per, std::unordered_map<std::string, Organisation> org, std::unordered_map<std::string, Anonymous> ans,
                            std::unordered_map<std::string, std::vector<tweet>> hashs, std::string username)
{
    users = per;
    org_user = org;
    ans_user = ans;

    Hashtags = hashs;

    li_user = new Base_User;
    if(users.count(username) == 1)
    {
        li_user = &(users[username]);
    }
    else if(org_user.count(username) == 1)
    {
        li_user = &(org_user[username]);
    }
    else
    {
        li_user = &(ans_user[username]);
    }
}

void main_profile::change_ro(int type)
{
    if(type == 1)
    {
        ui->ln_name->setReadOnly(true);
        ui->ln_username->setReadOnly(true);
        ui->ln_manager->setEnabled(true);
        ui->ln_phone->setReadOnly(true);
        ui->dt_birthday->setReadOnly(true);
        ui->te_bio->setReadOnly(true);
        ui->ln_country->setReadOnly(true);
        ui->ln_pass->setReadOnly(true);
        ui->ln_link->setReadOnly(true);
        ui->ln_header->setReadOnly(true);
    }

    else
    {
        ui->ln_name->setReadOnly(false);
        ui->ln_username->setReadOnly(false);
        ui->ln_phone->setReadOnly(false);
        ui->dt_birthday->setReadOnly(false);
        ui->te_bio->setReadOnly(false);
        ui->ln_country->setReadOnly(false);
        ui->ln_pass->setReadOnly(false);
        ui->ln_link->setReadOnly(false);
        ui->ln_header->setReadOnly(false);
    }
}
void main_profile::on_btn_editp_clicked()
{
    if(ans_user.count(li_user->get_username()) == 1)
    {
        ui->ln_username->setReadOnly(false);
        ui->ln_pass->setReadOnly(false);
    }
    else
    {
        change_ro(0);
    }
    ui->ln_pass->show();
    ui->lb_pass->show();
    ui->btn_save->show();
    ui->btn_discard->show();
    ui->lb_header->show();
    ui->ln_header->show();

    old_user.name = li_user->get_name();
    old_user.username = li_user->get_username();
    old_user.manager = li_user->get_manager_username();
    old_user.birth = li_user->get_birthday();
    old_user.phone = li_user->get_phone();
    old_user.country = li_user->get_country();
    old_user.link = li_user->get_link();
    old_user.bio = li_user->get_biography();
    old_user.pass = li_user->get_password();
    old_user.header = li_user->get_header();

    QMessageBox msg;
    msg.setWindowTitle("Message");
    msg.setText("You can edit your profile now.\nDont forgot click save to save your changes!!");
    msg.exec();
    ui->btn_editp->setEnabled(false);
}


void main_profile::on_btn_save_clicked()
{
    bool sPass = true, sName = true, sUsername = true, sPhone = true;
    if(li_user->get_name() == "Anonymous User")
    {
        if(ui->ln_username->text().toStdString() != old_user.username)
        {
            if(!ui->ln_username->text().toStdString().empty())
            {
                sUsername = li_user->set_username(ui->ln_username->text().toStdString());
            }
            else
            {
                QMessageBox msg;
                msg.setText("! Yor username can not be empty.");
                msg.setWindowTitle("Error");
                msg.exec();
            }
        }

        if(ui->ln_pass->text().toStdString() != old_user.pass)
        {
            if(!ui->ln_pass->text().toStdString().empty())
            {

               sPass = li_user->set_password(ui->ln_pass->text().toStdString());
            }
            else
            {
                QMessageBox msg;
                msg.setText("! Yor password can not be empty.");
                msg.setWindowTitle("Error");
                msg.exec();
            }
        }
    }
    else
    {
        if(!ui->ln_name->text().toStdString().empty())
        {
            li_user->set_name(ui->ln_name->text().toStdString());
        }
        else
        {
            QMessageBox msg;
            sName = false;
            msg.setText("! Yor name can not be empty.");
            msg.setWindowTitle("Error");
            msg.exec();
        }

        if(!ui->ln_username->text().toStdString().empty())
        {
            sUsername = li_user->set_username(ui->ln_username->text().toStdString());
        }
        else
        {
            QMessageBox msg;
            msg.setText("! Yor username can not be empty.");
            msg.setWindowTitle("Error");
            msg.exec();
        }

        if(users.count(li_user->get_username()) == 1)
        {
            li_user->set_birthday(ui->dt_birthday->text().toStdString());
        }

        li_user->set_country(ui->ln_country->text().toStdString());

        if(!ui->ln_phone->text().toStdString().empty())
        {
            li_user->set_phone(ui->ln_phone->text().toStdString());
        }
        else
        {
            QMessageBox msg;
            sPhone = false;
            msg.setText("! Yor phone number can not be empty.");
            msg.setWindowTitle("Error");
            msg.exec();

        }

        li_user->set_link(ui->ln_link->text().toStdString());
        li_user->set_biography(ui->te_bio->toPlainText().toStdString());
        li_user->set_header(ui->ln_header->text().toStdString());

        if(ui->ln_pass->text().toStdString() != old_user.pass)
        {
            if(!ui->ln_pass->text().toStdString().empty())
            {
                sPass = li_user->set_password(ui->ln_pass->text().toStdString());
            }

            else
            {
                QMessageBox msg;
                msg.setText("! Yor password can not be empty.");
                msg.setWindowTitle("Error");
                msg.exec();
            }
        }
    }

    if(sPass == true and sPhone == true and sUsername == true and sName == true)
    {
        QMessageBox msg;
        msg.setText("* Saved successfully");
        msg.setWindowTitle("Save");
        msg.exec();

        change_ro(1);
        ui->ln_pass->hide();
        ui->lb_pass->hide();
        ui->btn_save->hide();
        ui->btn_discard->hide();
        ui->lb_header->hide();
        ui->ln_header->hide();
        ui->btn_editp->setEnabled(true);
    }
}


void main_profile::on_btn_discard_clicked()
{
    fill_out_old();
    change_ro(1);
    if(org_user.count(li_user->get_username()) != 1)
    {
        ui->ln_manager->setEnabled(false);
    }
    ui->ln_pass->hide();
    ui->lb_pass->hide();
    ui->btn_save->hide();
    ui->btn_discard->hide();
    ui->lb_header->hide();
    ui->ln_header->hide();
    ui->btn_editp->setEnabled(true);
}
void main_profile::on_btn_logout_clicked()
{
    QMessageBox msg;
    msg.setWindowTitle("Exit");
    msg.setWindowTitle("Logout");
    msg.setText("Are you sure ?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (msg.exec() == QMessageBox::Yes)
    {
        put_users();
        this->close();
    }
}

void main_profile::on_btn_del_clicked()
{
//    li_user->Delete_Account()
}

