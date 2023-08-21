#include <iostream>
#include <string>
#include <ctype.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <QString>
#include <QDate>

#include "Twitterak_Class.hpp"
#include "Display_Class.hpp"
#include "User_Class.hpp"


twitterak::twitterak()
{
    read_users();
    read_from_file();
}

//------------------------------------------------------------------------------------------

std::unordered_map<std::string, Organisation> twitterak::get_org()
{
    return org_user;
}

std::unordered_map<std::string, user> twitterak::get_users()
{
    return users;
}

std::unordered_map<std::string, Anonymous> twitterak::get_ans()
{
    return ans_user;
}

std::unordered_map<std::string, std::vector<tweet>> twitterak::get_hashtags()
{
    return Hashtags;
}

void twitterak::put_users()
{
    std::ofstream wuser;
    std::ofstream wtweet;
    wuser.open("users.txt");
    wtweet.open("tweet.txt");

    for(auto i : users)
    {
        wuser << "type:user" << std::endl;
        wuser << "name:" << i.second.get_name() << std::endl;
        wuser << "username:" << i.second.get_username() << std::endl;
        wuser << "bio:" << i.second.get_biography() << std::endl;
        wuser << "link:" << i.second.get_link() << std::endl;
        wuser << "phone:" << i.second.get_phone() << std::endl;
        wuser << "header:" << i.second.get_header() << std::endl;
        wuser << "country:" << i.second.get_country() << std::endl;
        wuser << "birthday:" << i.second.get_birthday().toString("yyyy.MM.dd").toStdString() << std::endl;
        wuser << "password:" << i.second.get_password() << std::endl;
        wuser << "last_num:" << i.second.get_last_number() << std::endl;
        wuser << "picture:" << i.second.get_pic() << std::endl;

        wuser << "followers:";
        for(auto j : i.second.get_followers())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "followings:";
        for(auto j : i.second.get_following())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "passwords:";
        for(auto j : i.second.get_passwords())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;


        wuser << "my_mentions:" << std::endl;
        if(i.second.get_mention_trs().size() != 0)
        {
            for(auto j : i.second.get_mention_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "tweet_likes:" << std::endl;
        
        if(i.second.get_tweetlike_trs().size() != 0)
        {
            for(auto j : i.second.get_tweetlike_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "***" << std::endl;
        i.second.search_to_file(wtweet);
    }

    for (auto i : org_user)
    {
        wuser << "type:org" << std::endl;
        wuser << "name:" << i.second.get_name() << std::endl;
        wuser << "username:" << i.second.get_username() << std::endl;
        wuser << "bio:" << i.second.get_biography() << std::endl;
        wuser << "link:" << i.second.get_link() << std::endl;
        wuser << "phone:" << i.second.get_phone() << std::endl;
        wuser << "header:" << i.second.get_header() << std::endl;
        wuser << "country:" << i.second.get_country() << std::endl;
        wuser << "password:" << i.second.get_password() << std::endl;
        wuser << "last_num:" << i.second.get_last_number() << std::endl;
        wuser << "manager:" << i.second.get_manager_username() << std::endl;
        wuser << "picture:" << i.second.get_pic() << std::endl;
        wuser << "followers:";
        for(auto j : i.second.get_followers())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "followings:";
        for(auto j : i.second.get_following())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "passwords:";
        for(auto j : i.second.get_passwords())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;


        wuser << "my_mentions:" << std::endl;
        if(i.second.get_mention_trs().size() != 0)
        {
            for(auto j : i.second.get_mention_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "tweet_likes:" << std::endl;
        if(i.second.get_tweetlike_trs().size() != 0)
        {
            for(auto j : i.second.get_tweetlike_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "***" << std::endl;
        i.second.search_to_file(wtweet);
    }

    for (auto i : ans_user)
    {
        wuser << "type:ans" << std::endl;
        wuser << "username:" << i.second.get_username() << std::endl;
        wuser << "password:" << i.second.get_password() << std::endl;
        wuser << "picture:" << i.second.get_pic() << std::endl;

        wuser << "followings:";
        for(auto j : i.second.get_following())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;

        wuser << "passwords:";
        for(auto j : i.second.get_passwords())
        {
            wuser << j << ' ';
        }
        wuser << std::endl;     

        wuser << "my_mentions:" << std::endl;
        if(i.second.get_mention_trs().size() != 0)
        {
            for(auto j : i.second.get_mention_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }

        wuser << "tweet_likes:" << std::endl;
        if(i.second.get_tweetlike_trs().size() != 0)
        {
            for(auto j : i.second.get_tweetlike_trs())
            {
                wuser << j.first << ':';
                for(auto num : j.second)
                {
                    wuser << num << ' ';
                }
                wuser << std::endl;
            }
        }
        else
        {
            wuser << std::endl;
        }
        
        wuser << "***" << std::endl;
    }

    wuser.close();
    wtweet.close();
}

//------------------------------------------------------------------------------------------

void twitterak::read_users()
{
    std::ifstream ruser;
    ruser.open("users.txt");

    if(ruser)
    {
        std::string value;

        while (!ruser.eof())
        {
            ruser.ignore(1000, ':');
            getline(ruser, value);

            if(value == "user")
            {
                user u1;

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_name(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_username(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_biography(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_link(value);
                }


                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_phone(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_header(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_country(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    QString date = QString::fromStdString(value);
                    u1.set_birthday(QDate::fromString(date, "yyyy.MM.dd"));
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_pass_wHash(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_lastNum(std::stoi(value));
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    u1.set_pic(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    std::string follower;
                    std::stringstream str;
                    str << value;

                    while(str >> follower)
                    {
                        u1.add_followers(follower);
                    }
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    std::string following;
                    std::stringstream str;
                    str << value;

                    while(str >> following)
                    {
                        u1.add_following(following);
                    }
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    std::string pass;
                    std::stringstream str;
                    str << value;

                    while(str >> pass)
                    {
                        u1.add_to_passwords(pass);
                    }
                }

                ruser.ignore(1000, '\n');
                getline(ruser, value, '\n');
                while(value != "tweet_likes:")
                {
                    if(value.empty())
                    {
                        break;
                    }
                    
                    else
                    {
                        std::cout << "t1";
                        int size = value.size();
                        auto fcolon = value.find(':');
                        std::string user_name = value.substr(0, fcolon);
                        std::string line = value.substr(fcolon+1, size);
                        std::stringstream str;

                        str << line;
                        int num;
                        while(str >> num)
                        {
                            u1.push_myMentions(num, user_name);
                        }
                        std::cout << "t2";
                        getline(ruser, value, '\n');
                    }
                }

                getline(ruser, value, '\n');
                while(value != "***")
                {
                    if(value.empty())
                    {
                        break;
                    }
                    
                    else
                    {
                        int size = value.size();
                        auto fcolon = value.find(':');
                        std::string user_name = value.substr(0, fcolon);
                        std::string line = value.substr(fcolon+1, size);
                        std::stringstream str;

                        str << line;
                        int num;
                        while(str >> num)
                        {
                            u1.push_tweetLikes(num, user_name);
                        }

                        getline(ruser, value, '\n');
                    }
                }

                users[u1.get_username()] = u1;
            }

            else if(value == "org")
            {
                Organisation org1;

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_name(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_username(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_biography(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_link(value);
                }


                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_phone(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_header(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_country(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_pass_wHash(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_lastNum(std::stoi(value));
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_manager_username(*this,value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    org1.set_pic(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    std::string follower;
                    std::stringstream str;
                    str << value;

                    while(str >> follower)
                    {
                        org1.add_followers(follower);
                    }
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    std::string following;
                    std::stringstream str;
                    str << value;

                    while(str >> following)
                    {
                        org1.add_following(following);
                    }
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    std::string pass;
                    std::stringstream str;
                    str << value;

                    while(str >> pass)
                    {
                        org1.add_to_passwords(pass);
                    }
                }

                ruser.ignore(1000, '\n');
                getline(ruser, value, '\n');
                while(value != "tweet_likes:")
                {
                    if(value.empty())
                    {
                        break;
                    }
                    
                    else
                    {
                        int size = value.size();
                        auto fcolon = value.find(':');
                        std::string user_name = value.substr(0, fcolon);
                        std::string line = value.substr(fcolon+1, size);
                        std::stringstream str;

                        str << line;
                        int num;
                        while(str >> num)
                        {
                            org1.push_myMentions(num, user_name);
                        }

                        getline(ruser, value, '\n');
                    }
                }

                getline(ruser, value, '\n');
                while(value != "***")
                {
                    if(value.empty())
                    {
                        break;
                    }
                    
                    else
                    {
                        int size = value.size();
                        auto fcolon = value.find(':');
                        std::string user_name = value.substr(0, fcolon);
                        std::string line = value.substr(fcolon+1, size);
                        std::stringstream str;

                        str << line;
                        int num;
                        while(str >> num)
                        {
                            org1.push_tweetLikes(num, user_name);
                        }

                        getline(ruser, value, '\n');
                    }
                }

                org_user[org1.get_username()] = org1;
            }

            else if(value == "ans")
            {
                Anonymous ans1;

                ruser.ignore(1000, ':');
                getline(ruser, value);
                if(!value.empty())
                {
                    ans1.set_username(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value);
                if(!value.empty())
                {
                    ans1.set_pass_wHash(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    ans1.set_pic(value);
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    std::string following;
                    std::stringstream str;
                    str << value;

                    while(str >> following)
                    {
                        ans1.add_following(following);
                    }
                }

                ruser.ignore(1000, ':');
                getline(ruser, value, '\n');
                if(!value.empty())
                {
                    std::string pass;
                    std::stringstream str;
                    str << value;

                    while(str >> pass)
                    {
                        ans1.add_to_passwords(pass);
                    }
                }

                ruser.ignore(1000, '\n');
                getline(ruser, value, '\n');
                while(value != "tweet_likes:")
                {
                    if(value.empty())
                    {
                        break;
                    }
                    
                    else
                    {
                        int size = value.size();
                        auto fcolon = value.find(':');
                        std::string user_name = value.substr(0, fcolon);
                        std::string line = value.substr(fcolon+1, size);
                        std::stringstream str;

                        str << line;
                        int num;
                        while(str >> num)
                        {
                            ans1.push_myMentions(num, user_name);
                        }

                        getline(ruser, value, '\n');
                    }
                }

                getline(ruser, value, '\n');
                while(value != "***")
                {
                    if(value.empty())
                    {
                        break;
                    }
                    
                    else
                    {
                        int size = value.size();
                        auto fcolon = value.find(':');
                        std::string user_name = value.substr(0, fcolon);
                        std::string line = value.substr(fcolon+1, size);
                        std::stringstream str;

                        str << line;
                        int num;
                        while(str >> num)
                        {
                            ans1.push_tweetLikes(num, user_name);
                        }

                        getline(ruser, value, '\n');
                    }
                }

                ans_user[ans1.get_username()] = ans1;
            }
        }
    }
    ruser.close();
}


//------------------------------------------------------------------------------------------
// read tweets and mentions from a text file
void twitterak::read_from_file()
{
    std::ifstream read_file;
    read_file.open("tweet.txt");

    if (read_file.is_open())
    {
        while (!read_file.eof())
        {
            tweet tw;
            std::string tweet_type;
            std::string general;
            std::string time;
            std::string date;
            std::stringstream stm;
            //int number = 0;

            read_file.ignore(1000, ':');
            getline(read_file, tweet_type, '\n');

            if (tweet_type == "normal")
            {
                tw.set_tweetType("normal");
                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_name(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_user_name(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_number(std::stoi(general));

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_selfTweet(general);
                tw.fetch_hashtags(*this);

                read_file.ignore(1000, ':');
                getline(read_file, time, '\n');
                read_file.ignore(1000, ':');
                getline(read_file, date, '\n');
                tw.set_time(time, date);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                stm << general;
                while (stm >> general)
                {
                    tw.tweet_like(general);
                }

                getline(read_file, general, '\n');

                while (general != "---")
                {
                    mention mt;

                    int size = general.size();
                    auto fcolon = general.find(':');
                    std::string extra = general.substr(0, fcolon);
                    std::string num = general.substr(fcolon+1, size);

                    mt.set_number(std::stoi(num));
                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    mt.set_name(general);

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    mt.set_userName(general);

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    mt.set_mention(general);

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    stm << general;
                    while (stm >> general)
                    {
                        mt.set_likers(general);
                    }

                    tw.push_to_tweet(mt);
                    getline(read_file, general, '\n');
                }

                if (users.count(tw.get_user_name()))
                {       
                    users[tw.get_user_name()].Push_Tweet(tw);
                }
                else if (org_user.count(tw.get_user_name()))
                {       
                    org_user[tw.get_user_name()].Push_Tweet(tw);
                }
            }


            else if (tweet_type == "retweet")
            {
                tw.set_tweetType("retweet");
                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_name(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_user_name(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_number(std::stoi(general));
                

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_ownerName(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_ownerUser_name(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_ownerTweet(general);

                read_file.ignore(1000, ':');
                getline(read_file, time, '\n');
                read_file.ignore(1000, ':');
                getline(read_file, date, '\n');
                tw.set_time(time, date);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                stm << general;
                while (stm >> general)
                {
                    tw.tweet_like(general);
                }

                getline(read_file, general, '\n');
                while (general != "---")
                {
                    mention mt;

                    int size = general.size();
                    auto fcolon = general.find(':');
                    std::string extra = general.substr(0, fcolon);
                    std::string num = general.substr(fcolon+1, size);

                    mt.set_number(std::stoi(num));

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    mt.set_name(general);

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    mt.set_userName(general);

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    mt.set_mention(general);

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    stm << general;
                    while (stm >> general)
                    {
                        mt.set_likers(general);
                    }

                    tw.push_to_tweet(mt);
                    getline(read_file, general, '\n');
                }

                if (users.count(tw.get_user_name()))
                {       
                    users[tw.get_user_name()].Push_Tweet(tw);
                }
                else if (org_user.count(tw.get_user_name()))
                {       
                    org_user[tw.get_user_name()].Push_Tweet(tw);
                }
            }


            else if (tweet_type == "qoutetweet")
            {
                tw.set_tweetType("qoutetweet");
                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_name(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_user_name(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_number(std::stoi(general));

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_selfTweet(general);
                tw.fetch_hashtags(*this);
                
                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_ownerName(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_ownerUser_name(general);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                tw.set_ownerTweet(general);

                read_file.ignore(1000, ':');
                getline(read_file, time, '\n');
                read_file.ignore(1000, ':');
                getline(read_file, date, '\n');
                tw.set_time(time, date);

                read_file.ignore(1000, ':');
                getline(read_file, general, '\n');
                stm << general;
                while (stm >> general)
                {
                    tw.tweet_like(general);
                }

                getline(read_file, general, '\n');
                while (general != "---")
                {
                    mention mt;

                    int size = general.size();
                    auto fcolon = general.find(':');
                    std::string extra = general.substr(0, fcolon);
                    std::string num = general.substr(fcolon+1, size);

                    mt.set_number(std::stoi(num));

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    mt.set_name(general);

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    mt.set_userName(general);

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    mt.set_mention(general);

                    read_file.ignore(1000, ':');
                    getline(read_file, general, '\n');
                    stm << general;
                    while (stm >> general)
                    {
                        mt.set_likers(general);
                    }

                    tw.push_to_tweet(mt);
                    getline(read_file, general, '\n');
                }

                if (users.count(tw.get_user_name()))
                {       
                    users[tw.get_user_name()].Push_Tweet(tw);
                }
                else if (org_user.count(tw.get_user_name()))
                {       
                    org_user[tw.get_user_name()].Push_Tweet(tw);
                }
            }
        }
    }

    read_file.close();
}

//------------------------------------------------------------------------------------------

std::string twitterak::lower(std::string command)
{
    for(int i = 0; i < command.size(); i++)
    {
        command[i] = std::tolower(command[i]);
    }

    return command;
}
