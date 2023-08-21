#ifndef TWEET_HPP
#define TWEET_HPP
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include "Display_Class.hpp"
class twitterak;
class user;
class mention;
class Organisation;
//================================================================================ Tweet_Class ================================================================================ 
class tweet
{
        public:
//================ gets =====================
        std::string get_tweetType() const;                                      // returns the type of a tweet(quote/retweet)
        std::string get_sefTweet() const;                                       // returns the user's tweet
        std::string get_ownerName() const;                                      // returns the name of the owner of another user
        std::string get_ownerUser_name() const;                                 // returns the username of the owner of another user
        std::string get_ownerTweet() const;                                     // returns the tweet of the owner of another user
        std::string get_name() const;                                           // returns the name of the user
        std::string get_user_name() const;                                      // returns the username of the user
        int get_number() const;                                                 // returns the tweet's number
        int get_user_age() const;                                               // returns the age of the user 
        int get_like_number() const;
        int get_mentions_number() const;
        std::unordered_map<std::string, bool> operator~() const;
        std::string get_time();
        std::string get_date();
        std::vector<std::string> get_hashtags();
        std::unordered_map<std::string , std::vector<mention>> get_mentions();  // return the mentions map
//================ sets =====================
        void set_tweetType(std::string);
        void set_selfTweet(std::string);                                       // sets the user's tweet
        void set_ownerName(std::string);                                       // sets the name of the owner of another user
        void set_ownerUser_name(std::string);                                  // sets the username of the owner of another user
        void set_ownerTweet(std::string);                                      // sets the tweet of the owner of another user
        void set_name(std::string);                                            // sets the name of the user
        void set_user_name(std::string);                                       // sets the username of the user
        void set_number(int);                                                   // sets the tweet's number
        void set_user_age(user);                                                // sets the age of the user 
        void set_user_age();                                                    // sets the age of the user
        void set_time();
        void set_time(std::string , std::string);
//============ General functions =============
        bool tweet_like(std::string user_name);
        bool tweet_dislike(std::string user_name);
        void fetch_hashtags();                                       // finds and saves hashtags of user's tweet
        void fetch_hashtags(twitterak &app);
        void creat_mention(std::string, std::string, std::string);
        void delete_mentions(std::string);
        void dLike(std::string);
        void mention_like(std::string, int);
        void push_to_tweet(mention);
        void insert_to_file(std::ofstream &write);                                                  // put all tweets and mentions in a file
    private:
        int mentionNumber = 1;
        std::unordered_map<std::string, bool> likes;
        std::unordered_map<std::string , std::vector<mention>> tweet_mentions;
        std::string tweet_type;
        std::string self_tweet;
        std::string owner_name;
        std::string owner_username;
        std::string owner_tweet;
        std::vector<std::string> hashtags;
        std::string name;
        std::string user_name;
        int number;
        int user_age;
        // TD timeDate;
        std::string time;
        std::string date;
};

#endif
