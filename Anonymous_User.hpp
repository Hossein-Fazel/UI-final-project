#ifndef ANONYMOUS_USER_HPP
#define ANONYMOUS_USER_HPP

#include <iostream>
#include <unordered_map>

#include "Base_User.hpp"          

class twitterak;

class Anonymous : public Base_User
{
    public: 
        Anonymous();
        bool isin_following(std::string);
        void add_following(std::string);
        int get_following_num() const;
        std::unordered_set< std::string> get_following();
        std::unordered_map<std::string , std::unordered_set<int>> get_mention_trs();         // returns my_mention map
        std::unordered_map<std::string , std::unordered_set<int>> get_tweetlike_trs();       // returns tweet_likes map

        void push_myMentions(int, std::string);                   // save my mention traces
        void push_tweetLikes(int, std::string);                   // save my tweet likes traces
    private:
        std::unordered_set<std::string> following;

        std::unordered_map<std::string , std::unordered_set<int>> my_mentions;
        std::unordered_map<std::string , std::unordered_set<int>> tweetLikes;
};

#endif
