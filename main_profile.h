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
    std::string name , username, manager, phone, country, link, bio, pass, header, pic;
    QDate birthday;
};
class main_profile : public QMainWindow
{
    Q_OBJECT
public:
    explicit main_profile(QWidget *parent = nullptr);
    ~main_profile();
    void push_hashtag(std::string hashtag, tweet tw);
    void rm_hashtag(tweet tw);
    void change_ro(int type);
    void put_users();
    void set_vars(std::unordered_map<std::string, user> per,std::unordered_map<std::string, Organisation> org, std::unordered_map<std::string,
                  Anonymous> ans, std::unordered_map<std::string, std::vector<tweet>> hashs, std::string username);
    void fill_out_old();
    void fill_out();
    void show_tweet(Base_User *user, bool first);
    void fetch_hashtags(tweet tw);
    void to_lower(std::string &str);
    void delete_tweetlike(Base_User *user);
    void delete_mention(Base_User *user);
    void unfollow_followers(Base_User *user);
private slots:
    void on_btn_editp_clicked();
    void on_btn_save_clicked();
    void on_btn_discard_clicked();
    void on_btn_logout_clicked();
    void on_btn_del_clicked();
    void on_btn_search_clicked();
    void on_btn_showtweet_clicked();
    void on_radio_tweet_clicked();
    void on_btn_normalTweet_clicked();
    void on_radio_retweet_clicked();
    void on_btn_Retweet_clicked();
    void on_btn_Qoutetweet_clicked();
    void on_raido_qoutetweet_clicked();
    void on_btn_makMention_clicked();
    void on_btn_DeleteTweet_clicked();
    void on_btn_Follow_clicked();
    void on_btn_makeLike_Mention_clicked();
    void on_btn_makeLike_Tweet_clicked();
    void on_btn_showmention_clicked();
    void on_btn_change_clicked();
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
