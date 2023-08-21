#include <iostream>
#include <unordered_map>

#include "Anonymous_User.hpp"
#include "Twitterak_Class.hpp"
#include "Mention_class.hpp"              

//------------------------------------------------------------------------
// constructor
Anonymous::Anonymous()
{
    set_name("Anonymous User");
}

//------------------------------------------------------------------------

void Anonymous::add_following(std::string user_name)
{
    following.insert(user_name);
}

//------------------------------------------------------------------------

int Anonymous::get_following_num() const
{
    return following.size();
}


std::unordered_set< std::string> Anonymous::get_following()
{
    return following;
}

std::unordered_map<std::string , std::unordered_set<int>> Anonymous::get_mention_trs()         // returns my_mention map
{
    return my_mentions;
}


std::unordered_map<std::string , std::unordered_set<int>> Anonymous::get_tweetlike_trs()       // returns tweet_likes map
{
    return tweetLikes;
}

//------------------------------------------------------------------------
//check the user name exist in following
bool Anonymous::isin_following(std::string user_name)
{
    if(following.count(user_name) == 1)
    {
        return true;
    }

    else
    {
        return false;
    }
}

//------------------------------------------------------------------------

void Anonymous::push_tweetLikes(int number, std::string uName)
{
    tweetLikes[uName].insert(number);
}

//------------------------------------------------------------------------

void Anonymous::push_myMentions(int number, std::string uName)
{
    my_mentions[uName].insert(number);
}
