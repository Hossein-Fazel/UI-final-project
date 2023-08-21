#ifndef ORGANISATION_USER_HPP
#define ORGANISATION_USER_HPP
#include <iostream>
#include <map>
#include <fstream>
#include "Base_User.hpp"
#include "Display_Class.hpp"
class Organisation : public Base_User
{    
    public:
//========================================= Get_Functions =====================================
        std::string get_manager_username() const;                                // shows the usernsmae of an organisation's manager 
        int get_last_number() const;                                             // shows the last number of a tweet
        std::unordered_map <int, tweet> get_tweets();                           // shows organisation's tweets
        std::unordered_map<std::string , std::unordered_set<int>> get_mention_trs();         // returns my_mention map
        std::unordered_map<std::string , std::unordered_set<int>> get_tweetlike_trs();       // returns tweet_likes map
//========================================= Set_Functions =====================================
        bool set_manager_username(twitterak &, std::string);                       // sets the usernsmae of an organisation's manager
        void set_biography(std::string);                                         // sets the biography of an organisation
        void set_lastNum(int);
//================== General_Functions ====================
        void add_following(std::string);
        void delete_tweet(int);                                   // delete tweet
        void Push_Tweet(tweet);                                                  // push a tweet into a vector                          
        void increase_last_number();
        bool like(std::string ,int);
        bool add_mention(int, std::string, std::string , std::string);
        void like_mention(int, std::string, int); 
        void unfollow(std::string);                               // unfollow the user name
        void search_to_file(std::ofstream &write);
        std::unordered_set<std::string> get_following();
        void change_username(std::string str);            // change username in tweets
        void change_name(std::string str);                // change name in tweets
        void del_men(int, std::string);                           // delete a mention
        void del_tweetlike(int , std::string);                    // delete a tweet like
//==================== Save_Organisation_Traces ====================
        void push_myMentions(int, std::string);                                 // save my mention traces
        void push_tweetLikes(int, std::string);                                 // save my tweet likes traces
    private:
        user *manager;
        std::unordered_map<int , tweet> tweets;
        int last_number = 0;
        std::unordered_set<std::string> following;
        std::unordered_map<std::string , std::unordered_set<int>> my_mentions;
        std::unordered_map<std::string , std::unordered_set<int>> tweetLikes;
};

#endif
