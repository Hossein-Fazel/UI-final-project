#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_set>

#include "User_Class.hpp"
#include "Tweet_Class.hpp"
#include "Twitterak_Class.hpp"
#include "Mention_class.hpp"

//==================================================================  Get_Functions =================================================================

std::string tweet::get_tweetType() const                                                              // returns the type of tweet(quote/retweet)
{
    return tweet_type;
}

//------------------------------------------------------------------------

std::string tweet::get_sefTweet() const                                                                // returns the user's tweet
{
    return self_tweet;
}

//------------------------------------------------------------------------

std::string tweet::get_ownerName() const                                                                // returns the name of the owner of another user
{
    return owner_name;
}

//------------------------------------------------------------------------

std::string tweet::get_ownerUser_name() const                                                            // returns the username of the owner of another user
{
    return owner_username;
}

//------------------------------------------------------------------------

std::string tweet::get_ownerTweet() const                                                                 // returns the tweet of the owner of another user
{
    return owner_tweet;
}

//------------------------------------------------------------------------

std::string tweet::get_name() const                                                                        // returns the name of the user
{
    return name;
}

//------------------------------------------------------------------------

std::string tweet::get_user_name() const                                                                    // returns the username of the user
{
    return user_name;
}

//------------------------------------------------------------------------

int tweet::get_number() const                                                                                // returns the tweet's number
{
    return number;
}

//------------------------------------------------------------------------

int tweet::get_user_age() const                                                                               // returns the age of the user 
{
    return user_age;
}


std::string tweet::get_date()
{
    return date;
}

std::string tweet::get_time()
{
    return time;
}
//==================================================================  Set_Functions =================================================================

void tweet::set_tweetType(std::string type)                                                                    // sets the type of a tweet(quote/retweet)
{
    tweet_type = type;
}

//------------------------------------------------------------------------

void tweet::set_selfTweet(std::string tweet)                                                                    // sets the user's tweet
{
    self_tweet = tweet;
}

//------------------------------------------------------------------------

void tweet::set_ownerName(std::string name)                                                                      // sets the name of the owner of another user
{
    owner_name = name;
}

//------------------------------------------------------------------------

void tweet::set_ownerUser_name(std::string user_name)                                                            // sets the username of the owner of another user
{ 
    owner_username = user_name;
}

//------------------------------------------------------------------------

void tweet::set_ownerTweet(std::string tweet)                                                                      // sets the tweet of the owner of another user
{
    owner_tweet = tweet;
}

//------------------------------------------------------------------------

void tweet::set_name(std:: string got_name)                                                                             // sets the name of the user
{
    name = got_name;
}

//------------------------------------------------------------------------

void tweet::set_user_name(std:: string Guser_name)                                                                    // sets the username of the user
{
    user_name = Guser_name;
}

//------------------------------------------------------------------------

void tweet::set_number(int number)                                                                                   // sets the tweet's number
{
    this->number = number;
}

//------------------------------------------------------------------------

void tweet::set_user_age(user usr)                                                                                    // sets the age of the user 
{
    int user_birth;
    user_birth = std::stoi(usr.get_birthday().substr(0,4));
    user_age = 2023 - user_birth;
}

//------------------------------------------------------------------------

void tweet::set_user_age()                                                                                    // sets the age of the user 
{
    user_age = 2023;
}

//------------------------------------------------------------------------

void tweet::set_time()
{
    std::vector<std::string> time_part;
    time_t now = std::time(0);
    std::string dt = std::ctime(&now);

    std::string cm="";
    int size = dt.size();
    for(int i = 0; i < size; i++)
    {
        if(int(dt[i]) != 32)
        {
            cm += dt[i];
        }
        else
        {
            if(cm.empty())
            {
                continue;
            }
            else
            {
                time_part.push_back(cm);
                cm = "";
            }
        }
    }
    if(!cm.empty())
    {
        time_part.push_back(cm);
    }

    time = time_part[3];
    date = time_part[1] + ' ' + time_part[2] + ',' + time_part[4];
}

void tweet::set_time(std::string got_time, std::string got_date)
{
    time = got_time;
    date = got_date;
}

//================================================================  General_Functions ===============================================================

void tweet::edit_tweet(twitterak &app)                                                                                              // edits a tweet of a user
{
    if(user_age >= 18)
    {
        if(hashtags.size() != 0)
        {
            this->delete_hashtags(app);
            this->hashtags.clear();
        }
        std::string E_tweet;

        std::cout << this->get_number() << " : " << this->get_sefTweet() << std::endl;
        std::cout << "* Enter new text for tweet " << this->get_number() << " : ";
        std::getline(std::cin, E_tweet);

        this->set_selfTweet(E_tweet);
        this->fetch_hashtags(app);
        std::cout << "* You're tweet has been successfully changed.\n";
        // std::cin.ignore();
    }
    else
    {
        std::cout << "! Your age is less than 18.\n";
    }
}

//------------------------------------------------------------------------

void tweet::rq_tweet(twitterak &app, std::string type)                                                                // quote tweet or retweet
{
    tweet rq_tweet;
    rq_tweet.set_tweetType(type);
    rq_tweet.set_ownerTweet(this->self_tweet);
    rq_tweet.set_ownerUser_name(this->user_name);
    rq_tweet.set_ownerName(this->name);

    rq_tweet.set_name(app.li_user->get_name());
    rq_tweet.set_user_name(app.li_user->get_username());
    rq_tweet.set_number(app.li_user->get_last_number() + 1);
    app.li_user->increase_last_number();

    if(type == "qoute")
    {
        std::string tweet;
        std::cout << "$ your tweet : ";
        std::getline(std::cin, tweet);
        // std::cin.ignore();

        while (tweet.empty())
        {
            std::cout << "! Please enter your tweet\n";
            std::cout << "$ your tweet : ";
            std::getline(std::cin, tweet);
            // std::cin.ignore();
        }

        rq_tweet.set_selfTweet(tweet);
        rq_tweet.fetch_hashtags(app);
    }

    rq_tweet.set_time();
    app.li_user->Push_Tweet(rq_tweet);
}

//------------------------------------------------------------------------

int tweet::get_like_number() const
{
    return likes.size();
}
//------------------------------------------------------------------------

void tweet::fetch_hashtags()                                                    // finds and saves hashtags of user's tweet
{
    std::string hashtag;
    int tsize = this->self_tweet.size();

    for(int i = 0; i < tsize; i++)
    {
        if(this->self_tweet[i] == '#')
        {

            for(int j = i+1; j < tsize; j++)
            {
                if(this->self_tweet[j] != ' ')
                {
                    hashtag += this->self_tweet[j];
                }
                else
                {
                    if(!hashtag.empty())
                    {
                        for(int index = 0; index < hashtag.size(); index++)
                        {
                            hashtag[index] = std::tolower(hashtag[index]);
                        }
                        hashtags.push_back(hashtag);
                    }
                    hashtag = "";
                    i = j;
                    break;
                }
            }
        }
    }

    if(!hashtag.empty())
    {
        for(int index = 0; index < hashtag.size(); index++)
        {
            hashtag[index] = std::tolower(hashtag[index]);
        }
        hashtags.push_back(hashtag);
    }
}

void tweet::fetch_hashtags(twitterak &app)
{
    std::string hashtag;
        int tsize = this->self_tweet.size();

        for(int i = 0; i < tsize; i++)
        {
            if(this->self_tweet[i] == '#')
            {

                for(int j = i+1; j < tsize; j++)
                {
                    if(this->self_tweet[j] != ' ')
                    {
                        hashtag += this->self_tweet[j];
                    }
                    else
                    {
                        if(!hashtag.empty())
                        {
                            std::string lHashtag = app.lower(hashtag);
                            hashtags.push_back(lHashtag);
                            app.Hashtags[lHashtag].push_back(*this);
                        }
                        hashtag = "";
                        i = j;
                        break;
                    }
                }
            }
        }

        if(!hashtag.empty())
        {
            std::string lHashtag = app.lower(hashtag);
            hashtags.push_back(lHashtag);
            app.Hashtags[lHashtag].push_back(*this);
        }
}

std::vector<std::string> tweet::get_hashtags()
{
    return hashtags;
}
//-----------------------------------------------------------------------

std::unordered_map<std::string, bool> tweet::operator~() const
{
    return likes;
}

//-----------------------------------------------------------------------

bool tweet::tweet_like(std::string user_name)
{
    if(likes.count(user_name) == 0)
    {
        likes[user_name] = true;
        return true;
    }
    else
    {
        std::cout << "! You have already liked the tweet.\n";
        return false;
    }
}

//-----------------------------------------------------------------------

bool tweet::tweet_dislike(std::string user_name)
{
    if(likes.count(user_name))
    {
        likes.erase(user_name);
        return true;
    }
    else
    {
        std::cout << "! You have never lke this tweet\n";
        return false;
    }
}

//-----------------------------------------------------------------------

void tweet::creat_mention(std::string guserName, std::string gname)
{
    mention ment;

    std::string txt;
    std::cout << "$ your mention : ";
    std::getline(std::cin, txt);

    ment.set_mention(txt);
    ment.set_name(gname);
    ment.set_userName(guserName);
    ment.set_number(mentionNumber);

    mentionNumber += 1;

    tweet_mentions[guserName].push_back(ment);

    std::cout << "* Your mention was create successfully.\n";
}

//-----------------------------------------------------------------------

int tweet::get_mentions_number() const
{
    int size = 0;

    for(auto i:tweet_mentions)
    {
        size += i.second.size();
    }

    return size;
}

//-----------------------------------------------------------------------

void tweet::delete_hashtags(twitterak &app)
{
    for(auto hashtag :hashtags)
    {
        int vSize = app.Hashtags[hashtag].size();
        for(int i = 0; i < vSize; i++)
        {
            if(app.Hashtags[hashtag][i].get_number() == this->get_number() and app.Hashtags[hashtag][i].get_user_name() == this->get_user_name())
            {
                app.Hashtags[hashtag].erase(app.Hashtags[hashtag].begin() + i);
                break;
            }
        }
    }
}

//-----------------------------------------------------------------------

void tweet::delete_mentions(std::string got_userName)
{
    tweet_mentions.erase(got_userName);
}

//-----------------------------------------------------------------------

void tweet::dLike(std::string uName)
{
    likes.erase(uName);
}

//-----------------------------------------------------------------------

void tweet::mention_like(std::string uName, int mNumber)
{
    bool find_mention = false;
    for(auto &i:tweet_mentions)
    {
        for(auto &j:i.second)
        {
            if(j.get_number() == mNumber)
            {
                find_mention = true;
                if (j.mLikes.count(uName) == 1)
                {
                    std::cout << "! You have already liked this mention.\n";
                }
                else
                {
                    j.mLikes.insert(uName);
                    std::cout << "* Liked.\n";
                }

                break;
            }
        }

        if(find_mention)
        {
            break;
        }
    }
}


void tweet::push_to_tweet(mention mt)
{
    tweet_mentions[mt.get_username()].push_back(mt);
}

//-----------------------------------------------------------------------
// put all tweets and mentions in a file 
void tweet::insert_to_file()
{
    std::ofstream insert_file;
    insert_file.open("tweet.txt");


    insert_file << "tweet_type:" << get_tweetType() << std::endl;
    if (get_tweetType() == "normal")
    {
        insert_file << "name:" << get_name() << std::endl;
        insert_file << "username:" << get_user_name() << std::endl;
        insert_file << "number:" << get_number() << std::endl;
        insert_file << "tweet:" << get_sefTweet() << std::endl;
        insert_file << "time:" << get_time() << std::endl;
        insert_file << "date:" << get_date() << std::endl;

        insert_file << "likes:";
        for (auto i : likes)
        {
            insert_file << i.first << " ";
        }
        insert_file << std::endl;

        if (get_mentions_number() != 0)
        {
            for (auto j : tweet_mentions)
            { 
                for (auto k : j.second)
                {
                    insert_file << "mention_number:" << k.get_number() << std::endl;
                    insert_file << "name:" << k.get_name() << std::endl;
                    insert_file << "username:" << k.get_username() << std::endl;
                    insert_file << "text:" << k.get_mention() << std::endl;
                    insert_file << "likes:";

                    for (auto i : k.mLikes)
                    {
                        insert_file << i << " ";
                    }
                    insert_file << std::endl;
                }
            }
        }
            
        insert_file << "---" << std::endl;
    }

    //--------------------------------------------------
    else if (get_tweetType() == "retweet")
    {
        insert_file << "name:" << get_name() << std::endl;
        insert_file << "username:" << get_user_name() << std::endl;
        insert_file << "number:" << get_number() << std::endl;
        insert_file << "owner_name:" << get_ownerName() << std::endl;
        insert_file << "owner_username:" << get_ownerUser_name() << std::endl;
        insert_file << "owner_tweet:" << get_ownerTweet() << std::endl;
        insert_file << "time:" << get_time() << std::endl; 
        insert_file << "date:" << get_date() << std::endl;

        insert_file << "likes:";
        for (auto i : likes)
        {
            insert_file << i.first << " ";
        }
        insert_file << std::endl;


        if (get_mentions_number() != 0)
        {
            for (auto j : tweet_mentions)
            {
                for (auto k : j.second)
                {
                    insert_file << "mention_number:" << k.get_number() << std::endl;
                    insert_file << "name:" << k.get_name() << std::endl;
                    insert_file << "username:" << k.get_username() << std::endl;
                    insert_file << "text:" << k.get_mention() << std::endl;
                    insert_file << "likes:";
                    
                    for (auto i : k.mLikes)
                    {
                        insert_file << i << " ";
                    }
                }
            }
        }

        insert_file << "---" << std::endl;
    }

    //--------------------------------------------------
    else if (get_tweetType() == "qoutetweet")
    {
        insert_file << "name:" << get_name() << std::endl;
        insert_file << "username:" << get_user_name() << std::endl;
        insert_file << "number:" << get_number() << std::endl;
        insert_file << "tweet:" << get_sefTweet() << std::endl;
        insert_file << "owner_name:" << get_ownerName() << std::endl;
        insert_file << "owner_username:" << get_ownerUser_name() << std::endl;
        insert_file << "owner_tweet:" << get_ownerTweet() << std::endl;            
        insert_file << "time:" << get_time() << std::endl; 
        insert_file << "date:" << get_date() << std::endl;

        insert_file << "likes:";
        for (auto i : likes)
        {
            insert_file << i.first << " ";
        }
        insert_file << std::endl;


        if (get_mentions_number() != 0)
        {
            for (auto j : tweet_mentions)
            {
                for (auto k : j.second)
                {
                    insert_file << "mention_number:" << k.get_number() << std::endl;
                    insert_file << "name:" << k.get_name() << std::endl;
                    insert_file << "username:" << k.get_username() << std::endl;
                    insert_file << "text:" << k.get_mention() << std::endl;
                    insert_file << "likes:";
        
                    for (auto i : k.mLikes)
                    {
                        insert_file << i << " ";
                    }
                    insert_file << std::endl;
                }
            }
        }
        
        insert_file << "---" << std::endl;
    }


    insert_file.close();
}


