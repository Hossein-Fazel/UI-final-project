#include <iostream>
#include <string>
#include <unordered_map>
#include <QMessageBox>

#include "Twitterak_Class.hpp"
#include "Organisation_User.hpp"

//==================================================================  Get_Functions =================================================================

// shows the usernsmae of an organisation's manager
std::string Organisation::get_manager_username() const
{
    return manager->get_username();
}

//------------------------------------------------------------------------
// shows the last number of a tweet
int Organisation::get_last_number() const
{
    return last_number;
}

//------------------------------------------------------------------------
// shows organisation's tweets
std::unordered_map <int, tweet> Organisation::get_tweets()
{
    return tweets;
}

std::unordered_set<std::string> Organisation::get_following()
{
    return following;
}

std::unordered_map<std::string , std::unordered_set<int>> Organisation::get_mention_trs()         // returns my_mention map
{
    return my_mentions;
}


std::unordered_map<std::string , std::unordered_set<int>> Organisation::get_tweetlike_trs()       // returns tweet_likes map
{
    return tweetLikes;
}

//==================================================================  Set_Functions =================================================================
// sets the usernsmae of an organisation's manager
bool Organisation::set_manager_username(twitterak &app,std::string username)
{
    QMessageBox msg;
    if (username[0] == '@')
        username = remove_atsing(username);

    username = to_lower(username);

    if (app.users.count(username) == 1)
    {
        manager = &(app.users[username]);
        return true;
    }

    else
    {
        msg.setText("! The username doesn't exist.");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }
}

//------------------------------------------------------------------------
// sets the biography of an organisation
void Organisation::set_biography(std::string bio)
{
    if (bio.length() > 1100)
        Biography = bio.erase(1100, bio.length());

    else   
        Biography = bio;
}

//------------------------------------------------------------------------

void Organisation::set_lastNum(int num)
{
    last_number = num;
}

//================================================================  General_Functions ===============================================================

void Organisation::delete_tweet(int tNum)
{
    if(tweets.count(tNum) == 1)
    {
        tweets.erase(tNum);
    }
    else
    {
        std::cout << "! There is no tweet with this number.\n";
    }
}

//------------------------------------------------------------------------

void Organisation::unfollow(std::string user_name)
{
    followers.erase(user_name);
}

//------------------------------------------------------------------------
// push a tweet into a vector
void Organisation::Push_Tweet(tweet tw)
{
    tweets[tw.get_number()] = tw;
}

//------------------------------------------------------------------------

void Organisation::increase_last_number()
{
    last_number += 1;
}
//------------------------------------------------------------------------

bool Organisation::like(std::string user_name,int num)
{
    if(tweets.count(num) == 1)
    {
        bool status;
        status = tweets[num].tweet_like(user_name);
        return status;
    }
    else
    {
        std::cout << "! There is no tweet with this number.\n";
        return false;
    }
}

//------------------------------------------------------------------------

bool Organisation::add_mention(int tweet_number, std::string got_name, std::string got_user_name, std::string text)
{
    if(tweets.count(tweet_number) == 1)
    {
        tweets[tweet_number].creat_mention(got_user_name, got_name, text);
        return true;
    }
    else
    {
        std::cout << "! There is no tweet with this number.\n";
        return false;
    }
}

//------------------------------------------------------------------------

void Organisation::like_mention(int tNumber, std::string uName, int mNumber)
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

//================================================================  Save_Organisation_Traces ===============================================================

// save my mention traces
void Organisation::push_myMentions(int num, std::string uName)
{
    my_mentions[uName].insert(num);
}

//------------------------------------------------------------------------
// save my tweet likes traces
void Organisation::push_tweetLikes(int num, std::string uName)
{
    tweetLikes[uName].insert(num);
}
void Organisation::add_following(std::string user_name)
{
    following.insert(user_name);
}
//================================================================  Delete_Organisation_Traces ===============================================================
//------------------------------------------------------------------------
// delete a mention
void Organisation::del_men(int tNum, std::string user_name)                           
{
    if(tweets.count(tNum) == 1)
    {
        tweets[tNum].delete_mentions(user_name);
    }
}

//------------------------------------------------------------------------
// delete a tweet like
void Organisation::del_tweetlike(int tNum, std::string user_name)
{
    tweets[tNum].dLike(user_name);
}

//------------------------------------------------------------------------
void Organisation::search_to_file(std::ofstream &write)
{
    for (auto i : tweets)
    {
        i.second.insert_to_file(write);
    }
}

//------------------------------------------------------------------------
// change username in tweets
void Organisation::change_username(std::string str)
{
    for(auto &tweet : tweets)
    {
        tweet.second.set_user_name(str);
    }
}

//------------------------------------------------------------------------
// change name in tweets
void Organisation::change_name(std::string str)
{
    for(auto &tweet : tweets)
    {
        tweet.second.set_name(str);
    }
}
