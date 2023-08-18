#include "main_profile.h"
#include "ui_main_profile.h"

#include "Tweet_Class.hpp"
#include "User_Class.hpp"

#include <QMessageBox>
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
    ui->cm_header->hide();
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
        ui->cm_header->setEnabled(false);
        ui->gb_picture->setStyleSheet("background-color: gray;");
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

        QString style = "background-color: " + QString::fromStdString(li_user->get_header()) + ';';
        ui->gb_picture->setStyleSheet(style);

        ui->ln_phone->setText(QString::fromStdString(li_user->get_phone()));
        ui->ln_country->setText(QString::fromStdString(li_user->get_country()));
        ui->ln_link->setText(QString::fromStdString(li_user->get_link()));
        ui->te_bio->setText(QString::fromStdString(li_user->get_biography()));
        ui->ln_pass->setText(QString::fromStdString(li_user->get_password()));
        ui->cm_header->setCurrentText(QString::fromStdString(li_user->get_header()));
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
        ui->cm_header->setEnabled(false);

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
        ui->cm_header->setCurrentText(QString::fromStdString(old_user.header));
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
    ui->cm_header->show();

    old_user.name = ui->ln_name->text().toStdString();
    old_user.username = ui->ln_username->text().toStdString();
    old_user.manager = ui->ln_manager->text().toStdString();
    old_user.birth = ui->dt_birthday->text().toStdString();
    old_user.phone = ui->ln_phone->text().toStdString();
    old_user.country = ui->ln_country->text().toStdString();
    old_user.link = ui->ln_link->text().toStdString();
    old_user.bio = ui->te_bio->toPlainText().toStdString();
    old_user.pass = ui->ln_pass->text().toStdString();
    old_user.header = ui->cm_header->currentText().toStdString();

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
        li_user->set_header(ui->cm_header->currentText().toStdString());
        QString style = "background-color: " + QString::fromStdString(li_user->get_header()) + ';';
        ui->gb_picture->setStyleSheet(style);

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
        ui->cm_header->hide();
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
    ui->cm_header->hide();
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


void main_profile::on_btn_search_clicked()
{
    if(!ui->ln_search->text().toStdString().empty())
    {
        if(ui->ln_search->text().toStdString()[0] == '#')
        {
            std::string hashtag = ui->ln_search->text().toStdString();
            if(Hashtags.count(hashtag) == 1)
            {
                ui->tx_hashtag->clear();
                for(auto i : Hashtags[hashtag])
                {
                    QString tw;
                    if(i.get_tweetType() == "normal")
                    {
                         tw = QString::number(i.get_number()) + " : \n" + "username : " + QString::fromStdString(i.get_user_name()) +
                                 "\nname : " + QString::fromStdString(i.get_name()) + "\ntweet : " + QString::fromStdString(i.get_sefTweet())
                                 + "\n likes : " + QString::number(i.get_like_number()) + "\t mentions : "
                                 + QString::number(i.get_mentions_number()) + "  " + QString::fromStdString(i.get_time())
                                 + " " + QString::fromStdString(i.get_date()) + "\n\n";

                         ui->tx_hashtag->insertPlainText(tw);
                    }

                    else if(i.get_tweetType() == "retweet")
                    {
                         tw = QString::number(i.get_number()) + " : \n" + "username : " + QString::fromStdString(i.get_user_name()) +
                                 "\nname : " + QString::fromStdString(i.get_name()) + "\n    owner username : " + QString::fromStdString(i.get_ownerUser_name())
                                 + "\n    owner name : " + QString::fromStdString(i.get_ownerName()) +
                                 "\n    owner tweet : " + QString::fromStdString(i.get_sefTweet())
                                 + "\n likes : " + QString::number(i.get_like_number()) + "\t mentions : "
                                 + QString::number(i.get_mentions_number()) + "  " + QString::fromStdString(i.get_time())
                                 + " " + QString::fromStdString(i.get_date()) + "\n\n";

                         ui->tx_hashtag->insertPlainText(tw);
                    }

                    else
                    {
                         tw = QString::number(i.get_number()) + " : \n" + "username : " + QString::fromStdString(i.get_user_name()) +
                                 "\nname : " + QString::fromStdString(i.get_name()) + "\ntweet : " + QString::fromStdString(i.get_sefTweet()) +
                                 "\n    owner username : " + QString::fromStdString(i.get_ownerUser_name())
                                 + "\n    owner name : " + QString::fromStdString(i.get_ownerName()) +
                                 "\n    owner tweet : " + QString::fromStdString(i.get_sefTweet())
                                 + "\n likes : " + QString::number(i.get_like_number()) + "\t mentions : "
                                 + QString::number(i.get_mentions_number()) + "  " + QString::fromStdString(i.get_time())
                                 + " " + QString::fromStdString(i.get_date()) + "\n\n";

                         ui->tx_hashtag->insertPlainText(tw);
                    }
                }
            }

            else
            {
                QMessageBox msg;
                msg.setText("! This hashtag is not exist.");
                msg.setWindowTitle("Search");
                msg.exec();
            }
        }

        else if(ui->ln_search->text().toStdString()[0] == '@')
        {

        }

        else
        {
            QMessageBox msg;
            msg.setText("! Invalid search");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg;
        msg.setText("! search box is empty");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}



//=========================================================================== Tweet ===========================================================================
// radio button normal tweet
void main_profile::on_radio_tweet_clicked()
{
    ui->te_normalTweet->setEnabled(true);
    ui->btn_normalTweet->setEnabled(true);

    ui->ln_usrRetweet->setEnabled(false);
    ui->ln_tweetNumber_Retweet->setEnabled(false);
    ui->btn_Retweet->setEnabled(false);

    ui->ln_usrQoutetweet->setEnabled(false);
    ui->ln_tweetNumber_Qoutetweet->setEnabled(false);
    ui->te_qoutetweet->setEnabled(false);
    ui->btn_Qoutetweet->setEnabled(false);
}

//-------------------------------------------------------------------------------
// normal tweet
void main_profile::on_btn_normalTweet_clicked()
{
    if (ui->te_normalTweet->toPlainText().toStdString().empty())
    {
        QMessageBox msg;
        msg.setText("! Empty tweet text.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else
    {

    }
}

//-------------------------------------------------------------------------------
// raido button retweet
void main_profile::on_radio_retweet_clicked()
{
    ui->ln_usrRetweet->setEnabled(true);
    ui->ln_tweetNumber_Retweet->setEnabled(true);
    ui->btn_Retweet->setEnabled(true);

    ui->te_normalTweet->setEnabled(false);
    ui->btn_normalTweet->setEnabled(false);

    ui->ln_usrQoutetweet->setEnabled(false);
    ui->ln_tweetNumber_Qoutetweet->setEnabled(false);
    ui->te_qoutetweet->setEnabled(false);
    ui->btn_Qoutetweet->setEnabled(false);
}

//-------------------------------------------------------------------------------
// retweet
void main_profile::on_btn_Retweet_clicked()
{
    std::string username = ui->ln_usrRetweet->text().toStdString();
    int tweet_number = ui->ln_tweetNumber_Retweet->text().toInt();

    if ((ui->ln_usrRetweet->text().toStdString().empty()) || (ui->ln_tweetNumber_Retweet->text().toStdString().empty()))
    {
        QMessageBox msg;
        msg.setText("! Empty username or tweet number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if ((users.count(username) != 1) && (org_user.count(username) != 1) && (ans_user.count(username) != 1))
    {
        QMessageBox msg;
        msg.setText("! There is no user with this username.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if (!(li_user->get_tweets().count(tweet_number)))
    {
        QMessageBox msg;
        msg.setText("! There is no tweet with this number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else
    {

    }
}

//-------------------------------------------------------------------------------
// radio button qoutetweet
void main_profile::on_raido_qoutetweet_clicked()
{
    ui->ln_usrQoutetweet->setEnabled(true);
    ui->ln_tweetNumber_Qoutetweet->setEnabled(true);
    ui->te_qoutetweet->setEnabled(true);
    ui->btn_Qoutetweet->setEnabled(true);

    ui->te_normalTweet->setEnabled(false);
    ui->btn_normalTweet->setEnabled(false);

    ui->ln_usrRetweet->setEnabled(false);
    ui->ln_tweetNumber_Retweet->setEnabled(false);
    ui->btn_Retweet->setEnabled(false);
}

//-------------------------------------------------------------------------------
// qoutetweet
void main_profile::on_btn_Qoutetweet_clicked()
{
    std::string username = ui->ln_usrQoutetweet->text().toStdString();
    int tweet_number = ui->ln_tweetNumber_Qoutetweet->text().toInt();

    if ((ui->ln_usrQoutetweet->text().toStdString().empty()) || (ui->ln_tweetNumber_Qoutetweet->text().toStdString().empty())
        || (ui->te_qoutetweet->toPlainText().toStdString().empty()))
    {
        QMessageBox msg;
        msg.setText("! Empty username or tweet number or tweet text.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if ((users.count(username) != 1) && (org_user.count(username) != 1) && (ans_user.count(username) != 1))
    {
        QMessageBox msg;
        msg.setText("! There is no user with this username.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if (!(li_user->get_tweets().count(tweet_number)))
    {
        QMessageBox msg;
        msg.setText("! There is no tweet with this number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else
    {

    }
}

//=========================================================================== Make_Mention ===========================================================================

void main_profile::on_btn_makMention_clicked()
{
    std::string username = ui->ln_usrMention->text().toStdString();
    std::string mention_text = ui->te_mention_text->toPlainText().toStdString();
    int tweet_number = ui->ln_tweetNumber_Mention->text().toInt();

    if ((ui->ln_usrMention->text().toStdString().empty()) || (ui->ln_tweetNumber_Mention->text().toStdString().empty())
            || (ui->te_mention_text->toPlainText().toStdString().empty()))
    {
        QMessageBox msg;
        msg.setText("! Empty username or tweet number or mention text.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if ((users.count(username) != 1) && (org_user.count(username) != 1) && (ans_user.count(username) != 1))
    {
        QMessageBox msg;
        msg.setText("! There is no user with this username.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if (!(li_user->get_tweets().count(tweet_number)))
    {
        QMessageBox msg;
        msg.setText("! There is no tweet with this number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else
    {

    }
}

//=========================================================================== Fllow_User ===========================================================================

void main_profile::on_btn_Follow_clicked()
{
    std::string username = ui->ln_usrfollow->text().toStdString();

    if (ui->ln_usrfollow->text().toStdString().empty())
    {
        QMessageBox msg;
        msg.setText("! Empty username.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if ((users.count(username) != 1) && (org_user.count(username) != 1) && (ans_user.count(username) != 1))
    {
        QMessageBox msg;
        msg.setText("! There is no user with this username.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else
    {

    }
}

//=========================================================================== Delete_Tweet ===========================================================================

void main_profile::on_btn_DeleteTweet_clicked()
{
    int tweet_number = ui->ln_tweetNumber->text().toInt();

    if (ui->ln_tweetNumber->text().toStdString().empty())
    {
        QMessageBox msg;
        msg.setText("! Empty tweet number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if (!(li_user->get_tweets().count(tweet_number)))
    {
        QMessageBox msg;
        msg.setText("! There is no tweet with this number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else ()
    {

    }
}

//=========================================================================== Like ===========================================================================
//like a mention
void main_profile::on_btn_makeLike_Mention_clicked()
{
    std::string username = ui->ln_usrLike->text().toStdString();
    int tweet_number = ui->ln_tweetNumber_Like->text().toInt();
    int mention_number = ui->ln_mentionNumber_Like->text().toInt();

    if ((ui->ln_usrLike->text().toStdString().empty()) || (ui->ln_tweetNumber_Like->text().toStdString().empty()) ||
            (ui->ln_mentionNumber_Like->text().toStdString().empty()))
    {
        QMessageBox msg;
        msg.setText("! Empty username or tweet number or mention number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if ((users.count(username) != 1) && (org_user.count(username) != 1) && (ans_user.count(username) != 1))
    {
        QMessageBox msg;
        msg.setText("! There is no user with this username.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if (!(li_user->get_tweets().count(tweet_number)))
    {
        QMessageBox msg;
        msg.setText("! There is no tweet with this number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else ()
    {

    }
}

//-------------------------------------------------------------------------------
// like a tweet
void main_profile::on_btn_makeLike_Tweet_clicked()
{
    std::string username = ui->ln_usrLike_tweet->text().toStdString();
    int tweet_number = ui->ln_tweetNumber_Like_2->text().toInt();

    if ((ui->ln_usrLike_tweet->text().toStdString().empty()) || (ui->ln_tweetNumber_Like_2->text().toStdString().empty()))
    {
        QMessageBox msg;
        msg.setText("! Empty username or tweet number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if ((users.count(username) != 1) && (org_user.count(username) != 1) && (ans_user.count(username) != 1))
    {
        QMessageBox msg;
        msg.setText("! There is no user with this username.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if (!(li_user->get_tweets().count(tweet_number)))
    {
        QMessageBox msg;
        msg.setText("! There is no tweet with this number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else ()
    {

    }
}
