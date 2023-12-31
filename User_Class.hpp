#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <QDate>
#include "Base_User.hpp"
#include"Tweet_Class.hpp"
#include"Display_Class.hpp"
#include "Mention_class.hpp"
//================================================================================ User_Class ================================================================================ 
class user: public Base_User
{
//=================== Friends ===================
friend void tweet::insert_to_file(std::ofstream &write);
    public:
//===================== Gets ======================
        QDate get_birthday() const;                               // returns the date of birth of the user
        int get_last_number() const;                                    // returns the last tweet's number
        int get_following_num() const;
        std::unordered_set< std::string> get_following();
        std::unordered_map<std::string , std::unordered_set<int>> get_mention_trs();         // returns my_mention map
        std::unordered_map<std::string , std::unordered_set<int>> get_tweetlike_trs();       // returns tweet_likes map
//====================== sets =====================
        void set_birthday(QDate);                           // sets the date of birth of a user
        void set_lastNum(int);
//=============== General functions =================
        void delete_tweet(int);                    // delete tweet
        void Push_Tweet(tweet);                                    // push a tweet into a vector
        void increase_last_number();                                        // plus plus last_num variable
        void print_likers(int);
        bool like(std::string ,int);
        bool dislike(std::string, int);
        std::unordered_map<int, tweet> get_tweets();
        bool add_mention(int, std::string, std::string, std::string);
        void follow(twitterak &, std::string);
        void like_mention(int, std::string, int);
        void del_men(int, std::string);                           // delete a mention
        void del_tweetlike(int , std::string);                    // delete a tweet like
        void unfollow(std::string);                               // unfollow the user name
        void add_following(std::string);
        void search_to_file(std::ofstream &write);
        void change_username(std::string str);            // change username in tweets
        void change_name(std::string str);                // change name in tweets
//================== Save_User_Traces ==================
        void push_myMentions(int , std::string);
        void push_tweetLikes(int, std::string);
    private:
        QDate Birthday;
        int last_num = 0;
        std::unordered_map <int, tweet> tweets;
        std::unordered_set< std::string> following;
// ================================= User_Traces ============================
       std::unordered_map<std::string , std::unordered_set<int> > my_mentions;
       std::unordered_map<std::string , std::unordered_set<int> > tweetLikes;
};
#endif
