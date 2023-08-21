#include "main_profile.h"
#include "ui_main_profile.h"
#include "others_profile.h"
#include "mainwindow.h"

#include "Tweet_Class.hpp"
#include "User_Class.hpp"

#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <fstream>
#include <QPixmap>
#include <QDebug>

main_profile::main_profile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_profile)
{
    ui->setupUi(this);

//====================================== set additional settings =============================================
    change_ro(1);
    ui->ln_pass->hide();
    ui->lb_pass->hide();
    ui->btn_discard->hide();
    ui->btn_save->hide();
    ui->lb_header->hide();
    ui->cm_header->hide();

    ui->btn_change->hide();
    ui->lbl_pic_2->hide();
    ui->ln_pic->hide();
}

main_profile::~main_profile()
{
    delete ui;
}

void main_profile::fetch_hashtags(tweet tweet1)
{
    for(auto hashtag : tweet1.get_hashtags())
    {
        push_hashtag(hashtag, tweet1);
    }
}

void main_profile::to_lower(std::string &str)
{
    int size = str.size();
    for(int i = 0; i < size ; i ++)
    {
        str[i] = std::tolower(str[i]);
    }
}

void main_profile::rm_hashtag(tweet tw)
{
    for(auto hashtag :tw.get_hashtags())
    {
        int vSize = Hashtags[hashtag].size();
        for(int i = 0; i < vSize; i++)
        {
            if(Hashtags[hashtag][i].get_number() == tw.get_number() and Hashtags[hashtag][i].get_user_name() ==tw.get_user_name())
            {
                Hashtags[hashtag].erase(Hashtags[hashtag].begin() + i);
                break;
            }
        }
    }
}

void main_profile::fill_out()
{
    QPixmap pic_addr(QString::fromStdString(li_user->get_pic()));
    ui->lbl_pic->setPixmap(pic_addr.scaled(ui->lbl_pic->width(), ui->lbl_pic->height(), Qt::KeepAspectRatio));
    ui->ln_pic->setText(QString::fromStdString(li_user->get_pic()));

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

        ui->ln_pass->setText(QString());

        ui->box_deleteTweet->setEnabled(false);
        ui->box_makeTweet->setEnabled(false);

        ui->cm_header->setCurrentText(QString::fromStdString(li_user->get_header()));

        ui->ln_usrLike->setEnabled(false);
        ui->ln_tweetNumber_Like->setEnabled(false);
        ui->ln_mentionNumber_Like->setEnabled(false);
        ui->btn_makeLike_Mention->setEnabled(false);
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
            ui->ln_manager->setText(QString::fromStdString(li_user->get_manager_username()));

            ui->ln_follower->setText(QString::number(li_user->get_followers_num()));
            ui->ln_following->setEnabled(false);
        }

        else
        {

            ui->dt_birthday->setDate(li_user->get_birthday());

            ui->ln_manager->setEnabled(false);
            ui->ln_follower->setText(QString::number(li_user->get_followers_num()));
            ui->ln_following->setText(QString::number(li_user->get_following_num()));
        }

        QString style = "background-color: " + QString::fromStdString(li_user->get_header()) + ';';
        ui->gb_picture->setStyleSheet(style);

        ui->ln_phone->setText(QString::fromStdString(li_user->get_phone()));
        ui->ln_country->setText(QString::fromStdString(li_user->get_country()));
        ui->ln_link->setText(QString::fromStdString(li_user->get_link()));
        ui->te_bio->setText(QString::fromStdString(li_user->get_biography()));
        ui->ln_pass->setText(QString());
        ui->cm_header->setCurrentText(QString::fromStdString(li_user->get_header()));

        ui->ln_usrtweet->setText(QString::fromStdString(li_user->get_username()));
        show_tweet(li_user, true);
    }
}


void main_profile::fill_out_old()
{
    ui->ln_pic->setText(QString::fromStdString(old_user.pic));
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
            ui->dt_birthday->setDate(old_user.birthday);

            ui->ln_manager->setEnabled(false);
        }

        ui->ln_phone->setText(QString::fromStdString(old_user.phone));
        ui->ln_country->setText(QString::fromStdString(old_user.country));
        ui->ln_link->setText(QString::fromStdString(old_user.link));
        ui->te_bio->setText(QString::fromStdString(old_user.bio));
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
    std::ofstream wtweet;
    wuser.open("users.txt");
    wtweet.open("tweet.txt");

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
        wuser << "birthday:" << i.second.get_birthday().toString("yyyy.MM.dd").toStdString() << std::endl;
        wuser << "password:" << i.second.get_password() << std::endl;
        wuser << "last_num:" << i.second.get_last_number() << std::endl;
        wuser << "picture:" << i.second.get_pic() << std::endl;

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
        i.second.search_to_file(wtweet);
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
        wuser << "manager:" << i.second.get_manager_username() << std::endl;
        wuser << "picture:" << i.second.get_pic() << std::endl;
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
        i.second.search_to_file(wtweet);
    }

    for (auto i : ans_user)
    {
        wuser << "type:ans" << std::endl;
        wuser << "username:" << i.second.get_username() << std::endl;
        wuser << "password:" << i.second.get_password() << std::endl;
        wuser << "picture:" << i.second.get_pic() << std::endl;

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
    wtweet.close();
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
    else if (ans_user.count(username) == 1)
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
        ui->btn_change->show();
        ui->lbl_pic_2->show();
        ui->ln_pic->show();
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
    old_user.birthday = ui->dt_birthday->date();
    old_user.phone = ui->ln_phone->text().toStdString();
    old_user.country = ui->ln_country->text().toStdString();
    old_user.link = ui->ln_link->text().toStdString();
    old_user.bio = ui->te_bio->toPlainText().toStdString();
    old_user.header = ui->cm_header->currentText().toStdString();
    old_user.pic = ui->ln_pic->text().toStdString();

    QMessageBox msg;
    msg.setWindowTitle("Message");
    msg.setText("You can edit your profile now.\nDont forgot click save to save your changes!!");
    msg.exec();
    ui->btn_editp->setEnabled(false);
}


void main_profile::on_btn_save_clicked()
{
    bool sPass = true, sName = true, sUsername = true, sPhone = true, sPicture = true;
    if(li_user->get_name() == "Anonymous User")
    {
        if(ui->ln_username->text().toStdString() != old_user.username)
        {
            if(!ui->ln_username->text().toStdString().empty())
            {
                if(ui->ln_username->text().toStdString() != old_user.username)
                {
                    std::string old_username = old_user.username;
                    sUsername = li_user->set_username(ui->ln_username->text().toStdString());
//                    std::unordered_map <std::string,user>::const_iterator got = ans_user.find(old_username);

                    auto entry = ans_user.find(old_username);

                    if (entry != end(ans_user))
                    {
                        auto const val = std::move(entry->second);
                        ans_user.erase(entry);
                        ans_user.insert({ui->ln_username->text().toStdString(), std::move(val)});

                        li_user = &(ans_user[ui->ln_username->text().toStdString()]);
                    }
                }
            }
            else
            {
                QMessageBox msg;
                msg.setText("! Yor username can not be empty.");
                msg.setWindowTitle("Error");
                msg.exec();
            }
        }

        if(!ui->ln_pass->text().toStdString().empty())
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
            li_user->change_name(ui->ln_name->text().toStdString());
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
            if(ui->ln_username->text().toStdString() != old_user.username)
            {
                std::string old_username = old_user.username;
                if(users.count(old_username) == 1)
                {
                    sUsername = li_user->set_username(ui->ln_username->text().toStdString());
//                    std::unordered_map <std::string,user>::const_iterator got = users.find(old_username);

                    auto entry = users.find(old_username);

                    if (entry != end(users))
                    {
                        auto const val = std::move(entry->second);
                        users.erase(entry);
                        users.insert({ui->ln_username->text().toStdString(), std::move(val)});

                        li_user = &(users[ui->ln_username->text().toStdString()]);
                        ui->ln_usrtweet->setText(ui->ln_username->text());
                        li_user->change_username(ui->ln_username->text().toStdString());
                        show_tweet(li_user,true);
                    }
                }
                else if(org_user.count(old_username) == 1)
                {
                    sUsername = li_user->set_username(ui->ln_username->text().toStdString());
//                    std::unordered_map <std::string,user>::const_iterator got = users.find(old_username);

                    auto entry = org_user.find(old_username);

                    if (entry != end(org_user))
                    {
                        auto const val = std::move(entry->second);
                        org_user.erase(entry);
                        org_user.insert({ui->ln_username->text().toStdString(), std::move(val)});

                        li_user = &(org_user[ui->ln_username->text().toStdString()]);
                        li_user->change_username(ui->ln_username->text().toStdString());
                        ui->ln_usrtweet->setText(ui->ln_username->text());
                        show_tweet(li_user,true);
                    }
                }
            }
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
            li_user->set_birthday(ui->dt_birthday->date());
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

        if(!ui->ln_pass->text().toStdString().empty())
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

    li_user->set_pic(ui->ln_pic->text().toStdString());
    QPixmap pic_addr(QString::fromStdString(li_user->get_pic()));
    ui->lbl_pic->setPixmap(pic_addr.scaled(ui->lbl_pic->width(), ui->lbl_pic->height(), Qt::KeepAspectRatio));
    ui->ln_pic->setText(QString::fromStdString(li_user->get_pic()));

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

    if(org_user.count(li_user->get_username()) == 1)
    {
        ui->ln_manager->setEnabled(true);
    }
    else
    {
        ui->ln_manager->setEnabled(false);
    }

    ui->btn_change->hide();
    ui->lbl_pic_2->hide();
    ui->ln_pic->hide();
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
    ui->btn_change->hide();
    ui->lbl_pic_2->hide();
    ui->ln_pic->hide();
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
        MainWindow *window = nullptr;
        window = new MainWindow;
        window->show();
        this->close();
    }
}

void main_profile::on_btn_del_clicked()
{
    QMessageBox msg;
    msg.setWindowTitle("Exit");
    msg.setWindowTitle("Logout");
    msg.setText("? This operation cannot be reversed in any way\n Are you sure?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (msg.exec() == QMessageBox::Yes)
    {
        delete_tweetlike(li_user);
        delete_mention(li_user);
        unfollow_followers(li_user);
        if(ans_user.count(li_user->get_username()) != 1)
        {
            for(auto i : li_user->get_tweets())
            {
                rm_hashtag(i.second);
            }
        }
        if(users.count(li_user->get_username()) == 1)
        {
            users.erase(li_user->get_username());
        }

        else if(ans_user.count(li_user->get_username()) == 1)
        {
            ans_user.erase(li_user->get_username());
        }

        else if(org_user.count(li_user->get_username()) == 1)
        {
            org_user.erase(li_user->get_username());
        }
        put_users();
        MainWindow *window = nullptr;
        window = new MainWindow;
        window->show();
        this->close();
    }
}


void main_profile::delete_tweetlike(Base_User *user)
{
    for(auto i: user->get_tweetlike_trs())
    {
        if(i.first != user->get_username())
        {
            if(users.count(i.first) == 1)
            {
                for(auto j:i.second)
                {
                    if(users[i.first].get_tweets().count(j))
                    {
                        users[i.first].del_tweetlike(j ,user->get_username());
                    }
                }
            }

            else if(org_user.count(i.first) == 1)
            {
                for(auto j:i.second)
                {
                    if(org_user[i.first].get_tweets().count(j))
                    {
                        org_user[i.first].del_tweetlike(j ,user->get_username());
                    }
                }
            }
        }
    }
}


void main_profile::delete_mention(Base_User *user)
{
    for(auto i : user->get_mention_trs())
    {
        if(i.first != user->get_username())
        {
            if(users.count(i.first) == 1)
            {
                for(auto j : i.second)
                {
                    if(users[i.first].get_tweets().count(j) == 1)
                    {
                        users[i.first].del_men(j ,user->get_username());
                    }
                }
            }

            else if(org_user.count(i.first) == 1)
            {
                for(auto j : i.second)
                {
                    if(org_user[i.first].get_tweets().count(j) == 1)
                    {
                        org_user[i.first].del_men(j ,user->get_username());
                    }
                }
            }
        }
    }
}


void main_profile::unfollow_followers(Base_User *user)
{
    for(auto i : user->get_following())
    {
        if(users.count(i) == 1)
        {
            users[i].unfollow(user->get_username());
        }

        else if(org_user.count(i) == 1)
        {
            org_user[i].unfollow(user->get_username());
        }
    }
}

void main_profile::on_btn_search_clicked()
{
    if(!ui->ln_search->text().toStdString().empty())
    {
        if(ui->ln_search->text().toStdString()[0] == '#')
        {
            std::string hashtag = ui->ln_search->text().toStdString();
            to_lower(hashtag);
            hashtag.erase(0,1);
            if(Hashtags.count(hashtag) == 1)
            {
                ui->ln_search->clear();
                ui->tx_hashtag->clear();

                int size_vec = Hashtags[hashtag].size();
                if(size_vec == 0)
                {
                    QMessageBox msg;
                    msg.setText("! There is no tweet with this hashtag");
                    msg.setWindowTitle("Search");
                    msg.exec();

                    Hashtags.erase(hashtag);
                }



                else
                {
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
                                     "\n    owner tweet : " + QString::fromStdString(i.get_ownerTweet())
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
                                     "\n    owner tweet : " + QString::fromStdString(i.get_ownerTweet())
                                     + "\n likes : " + QString::number(i.get_like_number()) + "\t mentions : "
                                     + QString::number(i.get_mentions_number()) + "  " + QString::fromStdString(i.get_time())
                                     + " " + QString::fromStdString(i.get_date()) + "\n\n";

                             ui->tx_hashtag->insertPlainText(tw);
                        }
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
            std::string username = ui->ln_search->text().toStdString().erase(0, 1);
            to_lower(username);
            ui->ln_search->clear();
            ui->tx_hashtag->clear();
            if(users.count(username) == 1)
            {
                others_profile *op = nullptr;
                op = new others_profile;
                op->fill_out(&(users[username]), "user");
                op->show();
            }

            else if(org_user.count(username) == 1)
            {
                others_profile *op = nullptr;
                op = new others_profile;
                op->fill_out(&(org_user[username]), "org");
                op->show();
            }

            else if(ans_user.count(username) == 1)
            {
                others_profile *op = nullptr;
                op = new others_profile;
                op->fill_out(&(ans_user[username]), "ans");
                op->show();
            }

            else
            {
                QMessageBox msg;
                msg.setText("! This user does not exist");
                msg.setWindowTitle("Error");
                msg.exec();
            }
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

void main_profile::on_btn_showtweet_clicked()
{
    std::string username = ui->ln_usrtweet->text().toStdString();
    to_lower(username);

    if(username.empty())
    {
        QMessageBox msg;
        msg.setText("! Enter username");
        msg.setWindowTitle("Error");
        msg.exec();
    }
    else
    {
        if(users.count(username) == 1)
        {
            show_tweet(&(users[username]), 0);
        }
        else if(org_user.count(username) == 1)
        {
            show_tweet(&(org_user[username]), 0);
        }
        else if(ans_user.count(username) == 1)
        {
            QMessageBox msg;
            msg.setText("! This user can not be tweet");
            msg.setWindowTitle("Error");
            msg.exec();
        }
        else
        {
            QMessageBox msg;
            msg.setText("! This user does not exist");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }
}

void main_profile::show_tweet(Base_User *user , bool first)
{
    if(user->get_tweets().size() != 0)
    {
        ui->te_showTweet->clear();
        for(auto i : user->get_tweets())
        {
            QString tw;
            if(i.second.get_tweetType() == "normal")
            {
                 tw = QString::number(i.second.get_number()) + " : \n" +
                         "username : " + QString::fromStdString(i.second.get_user_name()) +
                         "\nname    : " + QString::fromStdString(i.second.get_name()) +
                         "\ntweet   : " + QString::fromStdString(i.second.get_sefTweet()) +
                         "\nlikes   : " + QString::number(i.second.get_like_number()) + "\t mentions : "
                         + QString::number(i.second.get_mentions_number()) + "  " + QString::fromStdString(i.second.get_time())
                         + " " + QString::fromStdString(i.second.get_date()) + "\n\n";

                 ui->te_showTweet->insertPlainText(tw);
            }

            else if(i.second.get_tweetType() == "retweet")
            {
                 tw = QString::number(i.second.get_number()) + " : \n" +
                         "username : " + QString::fromStdString(i.second.get_user_name()) +
                         "\nname    : " + QString::fromStdString(i.second.get_name()) +
                         "\n    owner username : " + QString::fromStdString(i.second.get_ownerUser_name()) +
                         "\n    owner name     : " + QString::fromStdString(i.second.get_ownerName()) +
                         "\n    owner tweet    : " + QString::fromStdString(i.second.get_ownerTweet()) +
                         "\nlikes   : " + QString::number(i.second.get_like_number()) + "\t mentions : "
                         + QString::number(i.second.get_mentions_number()) + "  " + QString::fromStdString(i.second.get_time())
                         + " " + QString::fromStdString(i.second.get_date()) + "\n\n";

                 ui->te_showTweet->insertPlainText(tw);
            }

            else
            {
                 tw = QString::number(i.second.get_number()) + " : \n" +
                         "username : " + QString::fromStdString(i.second.get_user_name()) +
                         "\nname    : " + QString::fromStdString(i.second.get_name()) +
                         "\ntweet   : " + QString::fromStdString(i.second.get_sefTweet()) +
                         "\n    owner username : " + QString::fromStdString(i.second.get_ownerUser_name())+
                         "\n    owner name     : " + QString::fromStdString(i.second.get_ownerName()) +
                         "\n    owner tweet    : " + QString::fromStdString(i.second.get_ownerTweet())+
                         "\nlikes   : " + QString::number(i.second.get_like_number()) + "\t mentions : "
                         + QString::number(i.second.get_mentions_number()) + "  " + QString::fromStdString(i.second.get_time())
                         + " " + QString::fromStdString(i.second.get_date()) + "\n\n";

                 ui->te_showTweet->insertPlainText(tw);
            }
        }
    }

    else
    {
        if(first != 1)
        {
            QMessageBox msg;
            msg.setText("! This user does not have any tweet");
            msg.setWindowTitle("Error");
            msg.exec();
        }
        else
        {
            ui->te_showTweet->clear();
        }
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
    std::string tweet_text = ui->te_normalTweet->toPlainText().toStdString();

    if (ui->te_normalTweet->toPlainText().toStdString().empty())
    {
        QMessageBox msg;
        msg.setText("! Empty tweet text.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else
    {
        tweet tw;
        tw.set_tweetType("normal");
        tw.set_name(li_user->get_name());
        tw.set_user_name(li_user->get_username());
        tw.set_number(li_user->get_last_number()+1);
        tw.set_selfTweet(tweet_text);
        tw.set_time();
        tw.fetch_hashtags();
        fetch_hashtags(tw);
        li_user->increase_last_number();
        li_user->Push_Tweet(tw);
        show_tweet(li_user,false);

        ui->te_normalTweet->clear();
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
    to_lower(username);
    int tweet_number = ui->ln_tweetNumber_Retweet->text().toInt();
    Base_User * usr = nullptr;

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



    else
    {
        bool status = true;
        if (users.count(username) == 1)
        {
            usr = &(users[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
                status = false;
            }
        }

        else if (org_user.count(username) == 1)
        {
            usr = &(org_user[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
                status = false;
            }
        }


        if(status == true)
        {
            tweet tw = usr->get_tweets()[tweet_number];
            tweet retweet;
            retweet.set_tweetType("retweet");

            retweet.set_name(li_user->get_name());
            retweet.set_user_name(li_user->get_username());
            retweet.set_number(li_user->get_last_number()+1);

            retweet.set_ownerName(tw.get_name());
            retweet.set_ownerUser_name(tw.get_user_name());
            retweet.set_ownerTweet(tw.get_sefTweet());

            retweet.set_time();
            li_user->increase_last_number();
            li_user->Push_Tweet(retweet);
            show_tweet(li_user,false);
        }

        ui->ln_usrRetweet->clear();
        ui->ln_tweetNumber_Retweet->clear();
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
    to_lower(username);
    std::string tweet_text = ui->te_qoutetweet->toPlainText().toStdString();
    int tweet_number = ui->ln_tweetNumber_Qoutetweet->text().toInt();
    Base_User * usr = nullptr;

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



    else
    {
        bool status = true;
        if (users.count(username) == 1)
        {
            usr = &(users[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
                status = false;
            }
        }

        else if (org_user.count(username) == 1)
        {
            usr = &(org_user[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
                status = false;
            }
        }

        if(status == true)
        {
            tweet tw = usr->get_tweets()[tweet_number];
            tweet qoute;
            qoute.set_tweetType("qoute");

            qoute.set_name(li_user->get_name());
            qoute.set_user_name(li_user->get_username());
            qoute.set_number(li_user->get_last_number()+1);
            qoute.set_selfTweet(tweet_text);

            qoute.set_ownerName(tw.get_name());
            qoute.set_ownerUser_name(tw.get_user_name());
            qoute.set_ownerTweet(tw.get_sefTweet());

            qoute.fetch_hashtags();
            fetch_hashtags(qoute);
            qoute.set_time();
            li_user->increase_last_number();
            li_user->Push_Tweet(qoute);
            show_tweet(li_user,false);
        }

        ui->ln_tweetNumber_Qoutetweet->clear();
        ui->te_qoutetweet->clear();
        ui->ln_usrQoutetweet->clear();
    }
}

//=========================================================================== Make_Mention ===========================================================================

void main_profile::on_btn_makMention_clicked()
{
    std::string username = ui->ln_usrMention->text().toStdString();
    to_lower(username);
    std::string mention_text = ui->te_mention_text->toPlainText().toStdString();
    int tweet_number = ui->ln_tweetNumber_Mention->text().toInt();
    Base_User * usr = nullptr;

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

    else
    {
        if (users.count(username) == 1)
        {
            usr = &(users[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
            }
            else
            {
                if(ans_user.count(li_user->get_username()) == 1)
                {
                    if(li_user->isin_following(usr->get_username()) == true)
                    {
                        bool status;
                        status = usr->add_mention(tweet_number,li_user->get_name(),li_user->get_username(),mention_text);

                        if(status == true)
                        {
                            li_user->push_myMentions(tweet_number, username);
                        }
                    }
                    else
                    {
                        QMessageBox msg;
                        msg.setText("! You must follow this user first");
                        msg.setWindowTitle("Error");
                        msg.exec();
                    }
                }

                else
                {
                    bool status;
                    status = usr->add_mention(tweet_number,li_user->get_name(),li_user->get_username(),mention_text);

                    if(status == true)
                    {
                        li_user->push_myMentions(tweet_number, username);
                    }
                }
            }
        }

        else if (org_user.count(username) == 1)
        {
            usr = &(org_user[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
            }
            else
            {
                if(ans_user.count(li_user->get_username()) == 1)
                {
                    if(li_user->isin_following(usr->get_username()) == true)
                    {
                        bool status;
                        status = usr->add_mention(tweet_number,li_user->get_name(),li_user->get_username(),mention_text);

                        if(status == true)
                        {
                            li_user->push_myMentions(tweet_number, username);
                        }
                    }
                    else
                    {
                        QMessageBox msg;
                        msg.setText("! You must follow this user first");
                        msg.setWindowTitle("Error");
                        msg.exec();
                    }
                }

                else
                {
                    bool status;
                    status = usr->add_mention(tweet_number,li_user->get_name(),li_user->get_username(),mention_text);

                    if(status == true)
                    {
                        li_user->push_myMentions(tweet_number, username);
                    }
                }
            }
        }

        else if (ans_user.count(username) == 1)
        {
            QMessageBox msg;
            msg.setText("! You must follow this user first");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }

    ui->ln_tweetNumber_Mention->clear();
    ui->te_mention_text->clear();
    ui->ln_usrMention->clear();

}

//=========================================================================== Fllow_User ===========================================================================

void main_profile::on_btn_Follow_clicked()
{
    std::string username = ui->ln_usrfollow->text().toStdString();
    to_lower(username);
    Base_User * usr = nullptr;

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

    else if (users.count(username) == 1)
    {
        usr = &(users[username]);
        usr->add_followers(li_user->get_username());
        li_user->add_following(username);
        ui->ln_following->setText(QString::number(li_user->get_following_num()));
    }

    else if (org_user.count(username))
    {
        usr = &(org_user[username]);
        usr->add_followers(li_user->get_username());
        li_user->add_following(username);
        ui->ln_following->setText(QString::number(li_user->get_following_num()));
    }

    else if(ans_user.count(username) == 1)
    {
        QMessageBox msg;
        msg.setText("! Anonymous users can't be followed.");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else if (li_user->get_username() == "Anonymous User")
    {
        if (!(users.count(username)))
        {
            QMessageBox msg;
            msg.setText("! You can only follow personal users.");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }

    ui->ln_usrfollow->clear();
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

    else
    {
        if(li_user->get_tweets().count(tweet_number) == 1)
        {
            rm_hashtag(li_user->get_tweets()[tweet_number]);
        }

        li_user->delete_tweet(tweet_number);
        show_tweet(li_user, true);
    }

    ui->ln_tweetNumber->clear();
}

//=========================================================================== Like ===========================================================================
//like a mention
void main_profile::on_btn_makeLike_Mention_clicked()
{
    std::string username = ui->ln_usrLike->text().toStdString();
    to_lower(username);
    int tweet_number = ui->ln_tweetNumber_Like->text().toInt();
    int mention_number = ui->ln_mentionNumber_Like->text().toInt();
    Base_User * usr = nullptr;

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


    else
    {
        if (users.count(username) == 1)
        {
            usr = &(users[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
            }

            else
            {
                usr->like_mention(tweet_number, li_user->get_username(), mention_number);
            }
        }

        else if (org_user.count(username) == 1)
        {
            usr = &(org_user[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
            }
            else
            {
                usr->like_mention(tweet_number, li_user->get_username(), mention_number);
            }
        }

        else if (ans_user.count(username) == 1)
        {
            QMessageBox msg;
            msg.setText("! This user can not have tweet");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }

    ui->ln_mentionNumber_Like->clear();
    ui->ln_tweetNumber_Like->clear();
    ui->ln_usrLike->clear();
}

//-------------------------------------------------------------------------------
// like a tweet
void main_profile::on_btn_makeLike_Tweet_clicked()
{
    std::string username = ui->ln_usrLike_tweet->text().toStdString();
    to_lower(username);
    int tweet_number = ui->ln_tweetNumber_Like_2->text().toInt();
    Base_User * usr = nullptr;

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

    else
    {
        if (users.count(username) == 1)
        {
            usr = &(users[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
            }
            else
            {
                if(ans_user.count(li_user->get_username()) == 1)
                {
                    if(li_user->isin_following(usr->get_username()) == true)
                    {
                        bool status;
                        status = usr->like(li_user->get_username(),tweet_number);
                        if(status == true)
                        {
                            li_user->push_tweetLikes(tweet_number, username);
                        }
                    }
                    else
                    {
                        QMessageBox msg;
                        msg.setText("! You must follow this user first");
                        msg.setWindowTitle("Error");
                        msg.exec();
                    }
                }

                else
                {
                    bool status;
                    status = usr->like(li_user->get_username(),tweet_number);
                    if(status == true)
                    {
                        li_user->push_tweetLikes(tweet_number, username);
                    }
                }
            }
        }

        else if (org_user.count(username) == 1)
        {
            usr = &(org_user[username]);
            if (!(usr->get_tweets().count(tweet_number)))
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number.");
                msg.setWindowTitle("Error");
                msg.exec();
            }
            else
            {
                if(ans_user.count(li_user->get_username()) == 1)
                {
                    if(li_user->isin_following(usr->get_username()) == true)
                    {
                        bool status;
                        status = usr->like(li_user->get_username(),tweet_number);
                        if(status == true)
                        {
                            li_user->push_tweetLikes(tweet_number, username);
                        }
                    }
                    else
                    {
                        QMessageBox msg;
                        msg.setText("! You must follow this user first");
                        msg.setWindowTitle("Error");
                        msg.exec();
                    }
                }

                else
                {
                    bool status;
                    status = usr->like(li_user->get_username(),tweet_number);
                    if(status == true)
                    {
                        li_user->push_tweetLikes(tweet_number, username);
                    }
                }
            }
        }

        else if (ans_user.count(username) == 1)
        {
            QMessageBox msg;
            msg.setText("! This user can not have tweet");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }

    ui->ln_tweetNumber_Like_2->clear();
    ui->ln_usrLike_tweet->clear();
}

void main_profile::on_btn_showmention_clicked()
{
    ui->te_showMention->clear();
    if(ui->ln_usrMention->text().toStdString().empty() and ui->ln_nummention->text().toStdString().empty())
    {
        QMessageBox msg;
        msg.setText("! The input boxes can not be empty");
        msg.setWindowTitle("Error");
        msg.exec();
    }

    else
    {
        std::string usr = ui->ln_usrmention->text().toStdString();
        to_lower(usr);

        int number = ui->ln_nummention->text().toInt();

        if(users.count(usr) == 1 or org_user.count(usr) == 1)
        {
            Base_User *user;

            if(users.count(usr) == 1)
            {
                user = &users[usr];
            }

            else if(org_user.count(usr) == 1)
            {
                user = &org_user[usr];
            }

            if(user->get_tweets().count(number) == 1)
            {
                QString ment;
                if(user->get_tweets()[number].get_mentions_number() != 0)
                {
                    for(auto vecmen : user->get_tweets()[number].get_mentions())
                    {
                        for(auto mention : vecmen.second)
                        {
                            ment = "mention no : " + QString::number(mention.get_number()) + '\n' +
                                    "name       : " + QString::fromStdString(mention.get_name()) + '\n' +
                                    "username   : " + QString::fromStdString(mention.get_username()) + '\n' +
                                    "text       : " +QString::fromStdString(mention.get_mention()) + '\n' +
                                    "likes      : " + QString::number(mention.get_likes_number()) + "\n\n";

                            ui->te_showMention->insertPlainText(ment);
                            ment = "";
                        }
                    }
                }

                else
                {
                    QMessageBox msg;
                    msg.setText("! There is no mentions for this tweet");
                    msg.setWindowTitle("Error");
                    msg.exec();
                }
            }

            else
            {
                QMessageBox msg;
                msg.setText("! There is no tweet with this number");
                msg.setWindowTitle("Error");
                msg.exec();
            }
        }

        else if(ans_user.count(usr))
        {
            QMessageBox msg;
            msg.setText("! This user can not have tweet");
            msg.setWindowTitle("Error");
            msg.exec();
        }

        else
        {
            QMessageBox msg;
            msg.setText("! This user does not exist");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }
}



void main_profile::on_btn_change_clicked()
{
    QString pic = QFileDialog::getOpenFileName();
    ui->ln_pic->setText(pic);
}

