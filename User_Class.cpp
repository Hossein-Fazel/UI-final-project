#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctype.h>
#include <iterator>
#include <cctype>

#include "QMessageBox"
#include "Twitterak_Class.hpp"
#include "Mention_class.hpp"

#include "User_Class.hpp"

//==================================================================  Get_Functions =================================================================

QDate user::get_birthday() const              // returns the date of birth of the user
{
    return Birthday;
}

//------------------------------------------------------------------------

int user::get_last_number() const                   // returns the last tweet's number
{
    return last_num;
}

//------------------------------------------------------------------------

int user::get_following_num() const                // returns the following numbers
{
    return following.size();
}

//------------------------------------------------------------------------

std::unordered_set< std::string> user::get_following()
{
    return following;
}

//------------------------------------------------------------------------

std::unordered_map<std::string , std::unordered_set<int>> user::get_mention_trs()         // returns my_mention map
{
    return my_mentions;
}

//------------------------------------------------------------------------

std::unordered_map<std::string , std::unordered_set<int>> user::get_tweetlike_trs()       // returns tweet_likes map
{
    return tweetLikes;
}

//==================================================================  Set_Functions =================================================================

void user::set_birthday(QDate birth)                                     // sets the date of birth of a user
{
    Birthday = birth;
}

//------------------------------------------------------------------------

void user::set_lastNum(int num)
{
    last_num = num;
}

//================================================================  General_Functions ===============================================================

//------------------------------------------------------------------------

void user::Push_Tweet(tweet tw)                                                                                  // push a tweet into a vector
{
    tweets[tw.get_number()] = tw;
}

//------------------------------------------------------------------------

void user::increase_last_number()                                                                                         // plus plus last_num variable
{
    last_num += 1;
}

//------------------------------------------------------------------------

bool user::like(std::string user_name, int number)
{
    if(tweets.count(number) == 1)
    {
        bool status;
        status = tweets[number].tweet_like(user_name);
        return status;
    }
    else
    {
        std::cout << "! There is no tweet with this number.\n";
        return false;
    }
}


//------------------------------------------------------------------------

std::unordered_map <int, tweet> user::get_tweets()
{
    return tweets;
}

//------------------------------------------------------------------------

bool user::add_mention(int tweet_number, std::string got_name, std::string got_user_name, std::string text)
{
    if(tweets.count(tweet_number) == 1)
    {
        tweets[tweet_number].creat_mention(got_user_name, got_name,text);
        return true;
    }
    else
    {
        std::cout << "! There is no tweet with this number.\n";
        return false;
    }
}


//------------------------------------------------------------------------

void user::like_mention(int tNumber, std::string uName, int mNumber)
{
    if(tweets.count(tNumber) == 1)
    {
        tweets[tNumber].mention_like(uName , mNumber);
    }
    else
    {
        std::cout << "! There is no tweet with this number.\n";
    }
}

//------------------------------------------------------------------------

void user::unfollow(std::string user_name)
{
    this->followers.erase(user_name);
}

//------------------------------------------------------------------------

void user::delete_tweet(int tNum)
{
    if(tweets.count(tNum) == 1)
    {
        tweets.erase(tNum);
    }
    else
    {
        QMessageBox msg;
        msg.setText("! There is no tweet with this number.");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}

void user::add_following(std::string user_name)
{
    following.insert(user_name);
}
//============================================== Delete_User_Traces =========================================

void user::del_men(int tNum, std::string user_name)                           // delete a mention
{
    if(tweets.count(tNum) == 1)
    {
        tweets[tNum].delete_mentions(user_name);
    }
}

//------------------------------------------------------------------------

void user::del_tweetlike(int tNum, std::string user_name)                    // delete a tweet like
{
    tweets[tNum].dLike(user_name);
}

//------------------------------------------------------------------------

void user::push_myMentions(int number, std::string uName)
{
    my_mentions[uName].insert(number);
}

//------------------------------------------------------------------------

void user::push_tweetLikes(int number, std::string uName)
{
    tweetLikes[uName].insert(number);
}

//------------------------------------------------------------------------
// 
void user::search_to_file(std::ofstream &write)
{
    for (auto i : tweets)
    {
        i.second.insert_to_file(write);
    }
}

//------------------------------------------------------------------------
// change username in tweets
void user::change_username(std::string str)
{
    for(auto &tweet : tweets)
    {
        tweet.second.set_user_name(str);
    }
}

//------------------------------------------------------------------------
// change name in tweets
void user::change_name(std::string str)
{
    for(auto &tweet : tweets)
    {
        tweet.second.set_name(str);
    }
}
