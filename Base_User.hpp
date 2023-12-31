#ifndef BASE_USER_HPP
#define BASE_USER_HPP
#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include <unistd.h>
#include <QDate>
#include "Tweet_Class.hpp"
class Base_User
{
    public:
//========================================= Set_Functions =====================================
        void set_name(std::string);                                       // sets the name of a user
        bool set_username(std::string);                                   // sets the username of a user with a validation
        bool set_password(std::string);                                   // sets the password of the user's account
        void set_pass_wHash(std::string);                                 // sets the password without hashing
        void set_link(std::string);                                       // sets the link of a user
        bool set_phone(std::string);                                      // sets the phone number of a user
        void set_header(std::string);                                     // sets the color of the header that user had chosen
        void set_country(std::string);                                    // sets the country of the user
        void set_pic(std::string path);                                   // sets the profile picture path
//======================================== Get_Functions ======================================
        std::string get_name() const;                                     // shows the name of the user
        std::string get_username() const;                                 // shows the username of the user
        std::string get_password() const;                                 // shows the password of the user's account
        std::string get_link() const;                                     // shows the link of the user
        std::string get_phone() const;                                    // shows the phone number of the user
        std::string get_header() const;                                   // shows the color of the header that user had chosen 
        std::string get_country() const;                                  // shows the country of the user
        int get_followers_num() const;                                    // shows the number of followers
        std::unordered_set <std::string> get_followers();                 // return followers set
        std::unordered_set <std::string> get_passwords();                 // return passwords set
        std::string get_pic();                                            // return frofile picture path
//======================================= general functions ====================================
        std::string to_lower(std::string);                                // makes a string a lowercase
        std::string remove_atsing(std::string);                           // removes @ from the first of the user name
        int Validating_Username(std::string);                             // the validation of a user's username
        int validate_password(std::string);                               // validating the acoount's password
        void add_followers(std::string);                                  // add a new follower to set
        bool validate_phone_number(std::string);                          // validate user's phone_number
        void add_to_passwords(std::string);                               // add to passwords set
//======================================= virtual functions =====================================
        virtual std::unordered_map<std::string , std::unordered_set<int>> get_mention_trs();
        virtual std::unordered_map<std::string , std::unordered_set<int>> get_tweetlike_trs();
        virtual std::string get_manager_username() const;
        virtual std::string get_biography() const;                        // returns the biography of the user
        virtual QDate get_birthday() const;                         // returns the date of birth of the user
        virtual int get_last_number() const;                              // returns the last number of tweet
        virtual int get_following_num() const;                            // returns the number of following 
        virtual std::unordered_map <int, tweet> get_tweets();                       // returns the tweets
        virtual std::unordered_set< std::string> get_following();
//========================= sets ==========================
        virtual void set_lastNum(int);
        virtual bool set_manager_username(twitterak &, std::string);
        virtual void set_biography(std::string);                          // sets the biography of a user
        virtual void set_birthday(QDate);                           // sets the date of birth of a user
//================== General_Functions ====================
        virtual void delete_tweet(int);                                   // delete tweet
        virtual void Push_Tweet(tweet);                                   // push a tweet into a vector
        virtual void increase_last_number();                              // plus plus last_num variable
        virtual bool like(std::string ,int);                              // like a tweet
        virtual bool add_mention(int, std::string, std::string,std::string);          // add a mention to a tweet
        virtual void like_mention(int, std::string, int);                 // like a mention
        virtual bool isin_following(std::string);                         // check the user name exist in following
        virtual void unfollow(std::string);                               // unfollow the user name
        virtual void add_following(std::string);
        virtual void search_to_file(std::ofstream &write);
        virtual void change_username(std::string str);
        virtual void change_name(std::string str);
//==================== Save_User_Traces ====================
        virtual void push_myMentions(int, std::string);                   // save my mention traces
        virtual void push_tweetLikes(int, std::string);                   // save my tweet likes traces
    private:
        std::string Full_Name;
        std::string Username;
        std::string Password;
        std::string Link;
        std::string Phone_Number;
        std::string Header;
        std::string Country;
        std::string picture;
    protected:
        std::string Biography;
        std::unordered_set <std::string> followers;                      // a set for followers of a specific user
        std::unordered_set <std::string> passwords;                      // a set for saving all passwords of a user
};

#endif
