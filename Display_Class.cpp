#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <QMessageBox>
#include <QDate>

#include "Display_Class.hpp"
#include "Twitterak_Class.hpp"
#include "sha256.h"

void display::show_normal(tweet tw)
{
    std::cout << tw.get_number() << " : " << tw.get_sefTweet() << std:: endl;
    std::cout << "likes : " << tw.get_like_number() << "\t";
    std::cout << "mentions : " << tw.get_mentions_number() << "  ";
    std::cout << tw.get_time();
    std::cout << " ";
    std::cout << tw.get_date();
    std::cout << "\n\n";
}

void display::show_qoute(tweet tw)
{
    std::cout << "tweet number : " << tw.get_number() << '\n';
    std::cout << "name         : " << tw.get_name() << std::endl ;
    std::cout << "username     : " << tw.get_user_name() << std::endl ;
    std::cout << "tweet text   :" << tw.get_sefTweet() << "\n\n";

    std::cout << "\towner name     : " << tw.get_ownerName() << "\n" ;
    std::cout << "\towner username : " << tw.get_ownerUser_name() << std::endl;
    std::cout << "\towner tweet    : " << tw.get_ownerTweet() << "\n\n";

    std::cout << "likes : " << tw.get_like_number() << " ";
    std::cout << "mentions : " << tw.get_mentions_number() << "  ";
    std::cout << tw.get_time();
    std::cout << " ";
    std::cout << tw.get_date();
    std::cout << "\n\n";
}

void display::show_re(tweet tw)
{
    std::cout << "tweet number : " << tw.get_number() << '\n';
    std::cout << "name         : " << tw.get_name() << std::endl ;
    std::cout << "username     : " << tw.get_user_name() <<"\n\n";

    std::cout << "\towner name     : " << tw.get_ownerName() << "\n" ;
    std::cout << "\towner username : " << tw.get_ownerUser_name() << std::endl;
    std::cout << "\towner tweet    : " << tw.get_ownerTweet() << "\n\n";

    std::cout << "likes : " << tw.get_like_number() << " ";
    std::cout << "mentions : " << tw.get_mentions_number() << "  ";
    std::cout << tw.get_time();
    std::cout << " ";
    std::cout << tw.get_date();
    std::cout << "\n\n";
}

//============================================================= Login_Functions ============================================================= 

bool display::login(twitterak &app, std::string user_name, std::string password)
{    
    SHA256 encrypt;

    user_name = app.lower(user_name);
    if(user_name[0] == '@')
    {
        user_name.erase(0,1);
    }

    if (app.users.count(user_name) == 1)                                           // login to personal user
    {
        if (app.users[user_name].get_password() == encrypt(password))
        {
            app.is_logedin = true;
            app.logedin_user = user_name;
            app.li_user = &(app.users[app.logedin_user]);

            QMessageBox msg;
            msg.setText("* Login was successful.");
            msg.setWindowTitle("Login");
            msg.exec();
            return true;
        }
        else
        {
            QMessageBox msg;
            msg.setText("! Your password is wrong.");
            msg.setWindowTitle("Error");
            msg.exec();
            return false;
        }
    }

    else if (app.org_user.count(user_name) == 1)                                      // login to organisation user
    {
        if (app.org_user[user_name].get_password() == encrypt(password))
        {
            app.is_logedin = true;
            app.logedin_user = user_name;
            app.li_user = &(app.org_user[app.logedin_user]);
            QMessageBox msg;
            msg.setText("* Login was successful.");
            msg.setWindowTitle("Login");
            msg.exec();
            return true;
        }
        else
        {
            QMessageBox msg;
            msg.setText("! Your password is wrong.");
            msg.setWindowTitle("Error");
            msg.exec();
            return false;
        }
    }

    else if (app.ans_user.count(user_name) == 1)                                          // login to anonymous user
    {
        if (app.ans_user[user_name].get_password() == encrypt(password))
        {
            app.is_logedin = true;
            app.logedin_user = user_name;
            app.li_user = &(app.ans_user[app.logedin_user]);
            QMessageBox msg;
            msg.setText("* Login was successful.");
            msg.setWindowTitle("Login");
            msg.exec();
            return true;
        }
        else
        {
            QMessageBox msg;
            msg.setText("! Your password is wrong.");
            msg.setWindowTitle("Error");
            msg.exec();
            return false;
        }
    }

    else
    {
        QMessageBox msg;
        msg.setText("! Your username is wrong.");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }
}

//------------------------------------------------------------------------------------------

void display::login(twitterak &app, std::string user_name)
{
    user_name = app.lower(user_name);
    if(user_name[0] == '@')
    {
        user_name.erase(0,1);
    }
    std::string password;

    std::cout << "$ Password : ";
    std::cin >> password;

    if (app.users.count(user_name) == 1)
    {
        if (app.users[user_name].get_password() == password)
        {
            app.is_logedin = true;
            app.logedin_user = user_name;
            app.li_user = &(app.users[app.logedin_user]);
            std::cout << "* Login was successful\n";
        }
        else
        {
            std::cout << "! Your password is incorrect\n";
        }
    }

    else if (app.org_user.count(user_name) == 1)                                      // login to organisation user
    {
        if (app.org_user[user_name].get_password() == password)
        {
            app.is_logedin = true;
            app.logedin_user = user_name;
            app.li_user = &(app.org_user[app.logedin_user]);
            std::cout << "* Login was successful\n";
        }
        else
        {
            std::cout << "! Your password is incorrect\n";
        }
    }

    else if (app.ans_user.count(user_name) == 1)                                          // login to anonymous user
    {
        if (app.ans_user[user_name].get_password() == password)
        {
            app.is_logedin = true;
            app.logedin_user = user_name;
            app.li_user = &(app.ans_user[app.logedin_user]);
            std::cout << "* Login was successful\n";
        }
        else
        {
            std::cout << "! Your password is incorrect\n";
        }
    }

    else
    {
        std::cout << "! Your username is incorrect\n";
    }
}

//------------------------------------------------------------------------------------------

void display::login(twitterak &app)
{
    std::string user_name, password;
    std::cout << "$ Username : ";
    std::cin >> user_name;
    user_name = app.lower(user_name);
    if(user_name[0] == '@')
    {
        user_name.erase(0,1);
    }

    std::cout << "$ Password : ";
    std::cin >> password;

    if (app.users.count(user_name) == 1)
    {
        if (app.users[user_name].get_password() == password)
        {
            app.is_logedin = true;
            app.logedin_user = user_name;
            app.li_user = &(app.users[app.logedin_user]);
            std::cout << "* Login was successful\n";
        }
        else
        {
            std::cout << "! Your password is incorrect\n";
        }
    }

    else if (app.org_user.count(user_name) == 1)                                      // login to organisation user
    {
        if (app.org_user[user_name].get_password() == password)
        {
            app.is_logedin = true;
            app.logedin_user = user_name;
            app.li_user = &(app.org_user[app.logedin_user]);
            std::cout << "* Login was successful\n";
        }
        else
        {
            std::cout << "! Your password is incorrect\n";
        }
    }

    else if (app.ans_user.count(user_name) == 1)                                          // login to anonymous user
    {
        if (app.ans_user[user_name].get_password() == password)
        {
            app.is_logedin = true;
            app.logedin_user = user_name;
            app.li_user = &(app.ans_user[app.logedin_user]);
            std::cout << "* Login was successful\n";
        }
        else
        {
            std::cout << "! Your password is incorrect\n";
        }
    }

    else
    {
        std::cout << "! Your username is incorrect\n";
    }
}

//============================================================= Sign-up_Function ============================================================= 

bool display::signup(twitterak &app, std::string Ausername, std::string Apassword, std::string profile)
{
    bool sUsername = true, sPass = true;
    Anonymous ans1;
    ans1.set_pic(profile);

    sUsername = ans1.set_username(Ausername);

    if(app.users.count(ans1.get_username()) == 1 or app.org_user.count(ans1.get_username()) == 1 or app.ans_user.count(ans1.get_username()) == 1)
    {
        QMessageBox msg;
        msg.setText("! Your username is not valid.");
        msg.setWindowTitle("Error");
        msg.exec();
        sUsername = false;
    }

    sPass = ans1.set_password(Apassword);
    ans1.set_header("gray");

    if(sPass == true and sUsername == true)
    {
        app.ans_user[ans1.get_username()] = ans1;
        QMessageBox msg;
        msg.setText("* Registration was successful.");
        msg.setWindowTitle("Signup");
        msg.exec();
        return true;
    }
    else
    {
        return false;
    }
}

//------------------------------------------------------------------------------------------

bool display::signupM(twitterak &app, std::string Aname, std::string Ausername, std::string Apassword, std::string manager,
                      std::string bio, std::string country, std::string phone, std::string link, std::string color, std::string profile)
{
    bool sUsername = true, sPass = true, sManager = true, sPhone = true;
    Organisation org1;
    org1.set_pic(profile);

    sUsername = org1.set_username(Ausername);

    if(app.users.count(org1.get_username()) == 1 or app.org_user.count(org1.get_username()) == 1 or app.ans_user.count(org1.get_username()) == 1)
    {
        QMessageBox msg;
        msg.setText("! Your username is not valid.");
        msg.setWindowTitle("Error");
        msg.exec();
        sUsername = false;
    }

    org1.set_name(Aname);
    sPass = org1.set_password(Apassword);
    if(!manager.empty())
    {
        sManager = org1.set_manager_username(app,manager);
    }

    if(!country.empty())
    {
        org1.set_biography(bio);
    }

    if(!country.empty())
    {
        org1.set_country(country);
    }

    if(!phone.empty())
    {
        sPhone = org1.set_phone(phone);
    }

    if(!link.empty())
    {
        org1.set_link(link);
    }

    if(!color.empty())
    {
        org1.set_header(color);
    }

    if(sManager == true and sPass == true and sUsername == true and sPhone == true)
    {
        app.org_user[org1.get_username()] = org1;
        QMessageBox msg;
        msg.setText("* Registration was successful.");
        msg.setWindowTitle("Signup");
        msg.exec();
        return true;
    }
    else
    {
        return false;
    }
}


//------------------------------------------------------------------------------------------

bool display::signup(twitterak &app,std::string Aname, std::string Ausername,std::string Apassword,std::string bio ,std::string country,
                     QDate birth ,std::string phone ,std::string link ,std::string color, std::string profile)
{
    bool sUsername = true, sPass = true, sPhone = true;
    user u1;
    u1.set_pic(profile);

    sUsername = u1.set_username(Ausername);

    if(app.users.count(u1.get_username()) == 1 or app.org_user.count(u1.get_username()) == 1 or app.ans_user.count(u1.get_username()) == 1)
    {
        QMessageBox msg;
        msg.setText("! Your username is not valid.");
        msg.setWindowTitle("Error");
        msg.exec();
        sUsername = false;
    }

    u1.set_name(Aname);
    sPass = u1.set_password(Apassword);
    if(!bio.empty())
    {
        u1.set_biography(bio);
    }

    if(!country.empty())
    {
        u1.set_country(country);
    }

    u1.set_birthday(birth);

    if(!phone.empty())
    {
        sPhone = u1.set_phone(phone);
    }

    if(!link.empty())
    {
        u1.set_link(link);
    }

    if(!color.empty())
    {
        u1.set_header(color);
    }

    if(sPass == true and sUsername == true and sPhone == true)
    {
        app.users[u1.get_username()] = u1;
        QMessageBox msg;
        msg.setText("* Registration was successful.");
        msg.setWindowTitle("Signup");
        msg.exec();
        return true;
    }
    else
    {
        return false;
    }
}

//------------------------------------------------------------------------------------------

void display::show_tweet(twitterak app, std::string user_name)
{
    if(app.users.count(user_name) == 1)
    {
        if (app.users[user_name].tweets.size() != 0)
        {
            for(auto our_tweet:app.users[user_name].tweets)
            {
                if(our_tweet.second.get_tweetType() == "normal")
                {
                    show_normal(our_tweet.second);
                }

                else if(our_tweet.second.get_tweetType() == "retweet")
                {
                    show_re(our_tweet.second);
                }

                else
                {
                    show_qoute(our_tweet.second);
                }
            }
        }
        else
        {
            std::cout << "! " << user_name << " does not have tweet yet.\n";
        }
    }

    else if(app.org_user.count(user_name) == 1)
    {
        if (app.org_user[user_name].tweets.size() != 0)
        {
            for(auto our_tweet:app.org_user[user_name].tweets)
            {
                if(our_tweet.second.get_tweetType() == "normal")
                {
                    show_normal(our_tweet.second);
                }

                else if(our_tweet.second.get_tweetType() == "retweet")
                {
                    show_re(our_tweet.second);
                }

                else
                {
                    show_qoute(our_tweet.second);
                }
            }
        }
        else
        {
            std::cout << "! " << user_name << " does not have tweet yet.\n";
        }
    }

    else
    {
        std::cout << "! There is no user with this username.\n";
    }
}

//------------------------------------------------------------------------------------------

void display::show_tweet(twitterak app,std::string user_name, int tNum)
{
    if(app.users.count(user_name) == 1)
    {
        if(app.users[user_name].tweets.count(tNum) == 1)
        {
            if(app.users[user_name].tweets[tNum].get_tweetType() == "normal")
            {
                show_normal(app.users[user_name].tweets[tNum]);
            }

            else if(app.users[user_name].tweets[tNum].get_tweetType() == "retweet")
            {
                show_re(app.users[user_name].tweets[tNum]);
            }

            else
            {
                show_qoute(app.users[user_name].tweets[tNum]);
            }
        }

        else
        {
            std::cout << "! There is no tweet with this number.\n";
        }
    }

    else if(app.org_user.count(user_name) == 1)
    {
        if(app.org_user[user_name].tweets.count(tNum))
        {
            if(app.org_user[user_name].tweets[tNum].get_tweetType() == "normal")
            {
                show_normal(app.org_user[user_name].tweets[tNum]);
            }

            else if(app.users[user_name].tweets[tNum].get_tweetType() == "retweet")
            {
               show_re(app.org_user[user_name].tweets[tNum]);
            }

            else
            {
                show_qoute(app.org_user[user_name].tweets[tNum]);
            }
        }

        else
        {
            std::cout << "! There is no tweet with this number.\n";
        }
    }

    else
    {
        std::cout << "! There is no user with this username.\n";
    }
}

//============================================================= Help_Function ============================================================= 

void display::help(twitterak &app)
{
    if(app.is_logedin == false)
    {
        std::cout << "\n";
        std::cout << "--------------------------------------- Help -----------------------------------------\n\n";
        std::cout << "login to your acount\n";
        std::cout << "~ login your_user_name your_password\n~ login your_user_name\n~ login \n\n";

        std::cout << "create a new account\n";
        std::cout << "~ signup your_user_name\n~ signup \n\n";

        std::cout << "close the app\n";
        std::cout << "~ exit (-y exit without confirm)\n~ quit (-y exit without confirm)\n~ q    (-y exit without confirm)\n\n";

        std::cout << "clear the screen\n";
        std::cout << "~ cls\n~ clear\n\n";

        std::cout << "-------------------------------------------------------------------------------------\n";
    }

    else
    {
        std::cout << "\n";
        std::cout << "--------------------------------------- Help -----------------------------------------\n\n";

        std::cout << "show your/another person account\n";
        std::cout << "~ profile\n";
        std::cout << "~ me\n";

        std::cout << "show another person profile :\n";
        std::cout << "~ profile @user_name\n\n";

        std::cout << "to edit your profile\n";
        std::cout << "~ edit profile edit_part value\n";
        std::cout << "! if your value is an string, put it between \"\" \n\n";

        std::cout << "logout from your account\n";
        std::cout << "~ logout\n\n";

        std::cout << "to delete your account\n";
        std::cout << "~ delete account\n\n";

        std::cout << "create a new tweet\n";
        std::cout << "~ tweet \n";
        std::cout << "~ tweet your_tweet_text\n\n";

        std::cout << "retweet a tweet\n";
        std::cout << "~ retweet user_name number_of_tweet\n\n";

        std::cout << "quotetweet\n";
        std::cout << "~ qoutetweet user_name number_of_tweet\n\n";

        std::cout << "like a tweet\n";
        std::cout << "~ like user_name number_of_tweet\n\n";

        std::cout << "dislike a tweet\n";
        std::cout << "~ dislike user_name number_of_tweet\n\n";
    
        std::cout << "show your/another person tweets\n";
        std::cout << "~ @me (show your tweets)\n";
        std::cout << "~ @your_user_name (show your tweets)\n";
        std::cout << "~ @user_name (show another person tweets)\n\n";

        std::cout << "show specific tweet \n";
        std::cout << "~ @user_name:number_of_tweet\n";
        std::cout << "~ @me:number_of_tweet\n\n";

        std::cout << "edit your tweet\n";
        std::cout << "~ edit tweet number_of_tweet\n\n";

        std::cout << "delete your tweet\n";
        std::cout << "~ delete tweet number_of_tweet\n\n";

        std::cout << "like a tweet\n";
        std::cout << "~ Like user_name:number_of_tweet\n\n";

        std::cout << "dislike a tweet\n";
        std::cout << "~ disike user_name:number_of_tweet\n\n";

        std::cout << "show likes of a tweet\n";
        std::cout << "~ @user_name:number_of_tweet:like\n\n";

        std::cout << "add mention to a tweet\n";
        std::cout << "~ mention username tweetNumber\n";
        std::cout << "~ mention @username tweetNumber\n\n";

        std::cout << "like a mention\n";
        std::cout << "~ like mention @username:tweet_number mention_number\n";
        std::cout << "~ like mention username:tweet_number mention_number\n\n";

        std::cout << "show mentions of a tweet\n";
        std::cout << "~ show mention username tweetNumber\n";
        std::cout << "~ show mention @username tweetNumber\n\n";

        std::cout << "follow a user\n";
        std::cout << "~ follow @username.\n";
        std::cout << "~ follow username.\n";

        std::cout << "clear the screen\n";
        std::cout << "~ cls\n~ clear\n\n";

        std::cout << "close the app\n";
        std::cout << "~ exit (-y exit without confirm)\n~ quit (-y exit without confirm)\n~ q    (-y exit without confirm)\n\n";

        std::cout << "------------------------------------------------------------------------------------\n";
    }
}

//============================================================= Show_Mention Function ============================================================= 

void display::show_mentions(twitterak app, std::string user_name, int tweet_number)
{
    if(app.users.count(user_name) == 1)
    {
        if(app.users[user_name].tweets.count(tweet_number) == 1)
        {
            std::cout << "username     : " << app.users[user_name].tweets[tweet_number].get_user_name() << std::endl;
            std::cout << "tweet number : " << app.users[user_name].tweets[tweet_number].get_number() << std::endl;
            std::cout << "tweet text   : " << app.users[user_name].tweets[tweet_number].get_sefTweet() << std::endl << std::endl;

            for (auto user :app.users[user_name].tweets[tweet_number].tweet_mentions)
            {
                for(auto ment:user.second)
                {
                    std::cout << "  mention no : " << ment.get_number() << std::endl;
                    std::cout << "  name       : " << ment.get_name() << std::endl;
                    std::cout << "  username   : " << ment.get_username() << std::endl;
                    std::cout << "  text       : " << ment.get_mention() << std::endl;
                    std::cout << "  likes      : " << ment.get_likes_number() << std::endl << std::endl;
                }
            }
        }
        else
        {
            std::cout << "! There is no tweet with this number.\n";
        }
    }
    
    else if(app.org_user.count(user_name) == 1)
    {
        if(app.org_user[user_name].tweets.count(tweet_number) == 1)
        {
            std::cout << "username     : " << app.org_user[user_name].tweets[tweet_number].get_user_name() << std::endl;
            std::cout << "tweet number : " << app.org_user[user_name].tweets[tweet_number].get_number() << std::endl;
            std::cout << "tweet text   : " << app.org_user[user_name].tweets[tweet_number].get_sefTweet() << std::endl << std::endl;

            for (auto user :app.org_user[user_name].tweets[tweet_number].tweet_mentions)
            {
                for(auto ment:user.second)
                {
                    std::cout << "  mention no : " << ment.get_number() << std::endl;
                    std::cout << "  name       : " << ment.get_name() << std::endl;
                    std::cout << "  username   : " << ment.get_username() << std::endl;
                    std::cout << "  text       : " << ment.get_mention() << std::endl;
                    std::cout << "  likes      : " << ment.get_likes_number() << std::endl << std::endl;
                }
            }
        }
        else
        {
            std::cout << "! There is no tweet with this number.\n";
        }
    }

    else
    {
        std::cout << "! There is no user with this username.\n";
    }
}
