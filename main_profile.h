#ifndef MAIN_PROFILE_H
#define MAIN_PROFILE_H

#include <QMainWindow>
#include <unordered_map>
#include <vector>

#include "Base_User.hpp"
#include "User_Class.hpp"
#include "Organisation_User.hpp"
#include "Anonymous_User.hpp"
#include "Tweet_Class.hpp"


namespace Ui {
class main_profile;
}

struct user_info
{
    std::string name , username, manager, birth, phone, country, link, bio, pass, header;
};

class main_profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_profile(QWidget *parent = nullptr);
    ~main_profile();

    void push_hashtag(std::string hashtag, tweet tw);
    void change_ro(int type);
    void put_users();
    void set_vars(std::unordered_map<std::string, user> per,std::unordered_map<std::string, Organisation> org, std::unordered_map<std::string, Anonymous> ans, std::unordered_map<std::string, std::vector<tweet>> hashs, std::string username);
    void fill_out_old();
    void fill_out();

private slots:
    void on_btn_editp_clicked();

    void on_btn_save_clicked();

    void on_btn_discard_clicked();

    void on_btn_logout_clicked();

    void on_btn_del_clicked();

private:
    Ui::main_profile *ui;

    Base_User *li_user = nullptr;

    std::unordered_map<std::string, user> users;
    std::unordered_map<std::string, Organisation> org_user;
    std::unordered_map<std::string, Anonymous> ans_user;

    std::unordered_map<std::string, std::vector<tweet>> Hashtags;

    user_info old_user;
};

#endif // MAIN_PROFILE_H
