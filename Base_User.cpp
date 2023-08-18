#include <iostream>
#include <unordered_set>
#include <cctype>
#include <ctype.h>
#include <QMessageBox>

#include "Base_User.hpp"
#include "Twitterak_Class.hpp"


//============================================== get functions ================================================
// shows the name of the user
std::string Base_User::get_name() const                                                       
{
    return Full_Name;
}

//------------------------------------------------------------------------
// shows the username of the user
std::string Base_User::get_username() const                                                    
{
    return Username;
}

//------------------------------------------------------------------------
// shows the number of followers
int Base_User::get_followers_num() const                                                     
{
    return this->followers.size();
}

//------------------------------------------------------------------------
// shows the link of the user
std::string Base_User::get_link() const                                          
{
    return Link;
}

//------------------------------------------------------------------------
// shows the phone number of the user
std::string Base_User::get_phone() const                                           
{
    return Phone_Number;
}

//------------------------------------------------------------------------
// shows the password of the user's account
std::string Base_User::get_password() const                                        
{
    return Password;
}

//------------------------------------------------------------------------
// shows the color of the header that user had chosen 
std::string Base_User::get_header() const                                          
{
    return Header;
}

//------------------------------------------------------------------------
// shows the country of the user
std::string Base_User::get_country() const                                         
{
    return Country;
}

//------------------------------------------------------------------------

std::unordered_set <std::string> Base_User::get_followers()
{
    return followers;
}

//------------------------------------------------------------------------

std::unordered_set <std::string> Base_User::get_passwords()                 // return passwords set
{
    return passwords;
}

//=============================================== set functions ===============================================
// sets the name of a user
void Base_User::set_name(std::string name)                                               
{
    Full_Name = name;
}


//------------------------------------------------------------------------
// sets the username of a user with a validation
bool Base_User::set_username(std::string user_name)
{
    if ((Validating_Username(user_name)) == 0)
    {
        QMessageBox msg;
        msg.setText("! Username must have at least 5 characters.");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }

    else if ((Validating_Username(user_name)) == -1)
    {
        QMessageBox msg;
        msg.setText("! Username must not have characters.");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }

    else if ((Validating_Username(user_name)) == -2)
    {
        QMessageBox msg;
        msg.setText("! Username must not be the commands of the program.");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }

    else
    {
        if (Username[0] == '@')
            Username = remove_atsing(user_name);

        Username = to_lower(user_name);
        return true;
    }
}

//------------------------------------------------------------------------
// sets the password of the user's account
bool Base_User::set_password(std::string input_pass)
{

    if ((validate_password(input_pass)) == 1)
    {
        Password = input_pass;
        passwords.insert(Password);
    }
    else if ((validate_password(input_pass)) == 0)
    {
        QMessageBox msg;
        msg.setText("! Wrong Password.Your Password must include number, letter and charector.");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }
    else if ((validate_password(input_pass)) == -1)
    {
        QMessageBox msg;
        msg.setText("! Duplicate Password.This password is already repeated.");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }
    else if ((validate_password(input_pass)) == 2)
    {
        QMessageBox msg;
        msg.setText("! Short Password.You're password at least must be 6 character");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }
}

//------------------------------------------------------------------------

void Base_User::set_pass_wHash(std::string hashPass)
{
    Password = hashPass;
}

//------------------------------------------------------------------------
// sets the link of a user
void Base_User::set_link(std::string link)                                              
{
    const std::string Https = "https://";
    Link = Https + link;
}

//------------------------------------------------------------------------
// sets the phone number of a user
bool Base_User::set_phone(std::string phone)
{
    if (!(validate_phone_number(phone)))
    {
        QMessageBox msg;
        msg.setText("! Your phone number is invalid.");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }
    else
    {
        Phone_Number = phone;
        return true;
    }
}                 

//------------------------------------------------------------------------
// sets the color of the header that user had chosen
void Base_User::set_header(std::string input_header)                                   
{
    Header = input_header;
}

//------------------------------------------------------------------------
// sets the country of the user
void Base_User::set_country(std::string country)                                       
{
    Country = country;
}

// ============================================= general functions ===============================================
// push to passwords set
void Base_User::add_to_passwords(std::string pass)
{
    passwords.insert(pass);
}

//------------------------------------------------------------------------

// validating the acoount's password
int Base_User::validate_password(std::string pass)   
{
    if (pass.length() < 6)
        return 2;
    
    for (int i = 0; i < pass.length(); ++i)
    {
        if (!isalnum(pass[i]))
            return 1;
    }
    
    pass = pass;

    if (passwords.count(pass) == 1)
        return -1;

    return 0;
}

//------------------------------------------------------------------------

void Base_User::add_followers(std::string uName)
{
    this->followers.insert(uName);
}

//------------------------------------------------------------------------
// the validation of a user's username
int Base_User::Validating_Username(std::string user_name)                              
{
    if (user_name.length() < 5)
        return 0;

    for (int i = 0; i < user_name.length(); ++i)
    {
        if (!isalnum(user_name[i]))
            return -1;
    }
   
    user_name = to_lower(user_name);

    if ((user_name == "help") or (user_name == "login") or (user_name == "signup") or (user_name == "edit") 
        or (user_name == "exit") or (user_name == "delete account") or (user_name == "like") or (user_name == "profile") 
        or (user_name == "quit")or (user_name == "logout") or (user_name == "delete tweet") or (user_name == "edit tweet"))
    {
        return -2;
    }
        

    return 1;
}

//------------------------------------------------------------------------
// makes a string lowercase
std::string Base_User::to_lower(std::string str)                                        
{
    for (int i = 0; i < str.length(); ++i)
        str[i] = tolower(str[i]);

    return str;
}

//------------------------------------------------------------------------
// removes @ from the first of the user name
std::string Base_User::remove_atsing(std::string str)                                   
{
    return str.erase(0, 1);
}

//------------------------------------------------------------------------
// logs out of the user's account
void Base_User::Logout(twitterak & app)
{
    app.is_logedin = false;
    std::cout << "* You have successfully logged out.\n";
}

//------------------------------------------------------------------------
// validate user's phone_number
bool Base_User::validate_phone_number(std::string phone)                            
{
    for (int i = 0; i < phone.size(); i++)
    {
        if ((isdigit(phone[i])) == 0)
        {
            return false;
            break;
        }
    }

    if (phone.length() == 11 || phone.length() == 12 || phone.length() == 13)
        return true;
        
    else 
        return false;

    return true;
}

//============================================== Virtuals ===============================================
// does not have access to use this function from parent class
void Base_User::follow(twitterak & app, std::string uName)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// sets the biography of a user
void Base_User::set_biography(std::string bio)
{
    if (bio.length() > 160)
        Biography = bio.erase(160, bio.length());

    else   
        Biography = bio;
}

//------------------------------------------------------------------------
// shows the biography of the user
std::string Base_User::get_biography() const
{
    return Biography;
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
std::string Base_User::get_birthday() const
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
int Base_User::get_last_number() const
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
int Base_User::get_following_num() const
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::set_birthday(std::string birth)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::Delete_Account(twitterak & app)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::Show_Profile(twitterak & app)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::Edit(twitterak & app, std::string edit_part, std::string value)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::edit_tweet(int tNum, twitterak & app)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::Tweet(std::string tweet_text, twitterak & app)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::Push_Tweet(tweet tw)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::increase_last_number()
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::print_likers(int number)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
bool Base_User::like(std::string username, int number)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
bool Base_User::dislike(std::string username, int number)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
bool Base_User::add_mention(int tweet_number, std::string got_name, std::string got_username)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::push_myMentions(int number, std::string uName)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::push_tweetLikes(int number, std::string uName)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::pop_tweetLikes(int number, std::string uName)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::del_myMentions(twitterak & app)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::cls_hashtags(twitterak & app)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::del_tweetLikes(twitterak & app)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
void Base_User::like_mention(int tNumber, std::string uName, int mNumber)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// does not have access to use this function from parent class
std::unordered_map <int, tweet> Base_User::get_tweets()
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
//check the user name exist in following
bool Base_User::isin_following(std::string)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// delete a mention
void Base_User::del_men(int, std::string)
{
    std::cout << "! This feature can't be reached for your account.\n";
}                     

//------------------------------------------------------------------------
// delete a tweet like
void Base_User::del_tweetlike(int tNum, std::string user_name)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------

void Base_User::unfollow(std::string user_name)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------

void Base_User::unfollow_followers(twitterak &app)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------

std::unordered_set< std::string> Base_User::get_following()
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// returns my_mention map
std::unordered_map<std::string , std::unordered_set<int>> Base_User::get_mention_trs()
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------
// returns tweet_likes map
std::unordered_map<std::string , std::unordered_set<int>> Base_User::get_tweetlike_trs()
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------

void Base_User::delete_tweet(int tNum, twitterak &app)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------

void Base_User::add_following(std::string user_name)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------

void Base_User::set_lastNum(int num)
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------

void Base_User::search_to_file()
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------

std::string Base_User::get_manager_username() const
{
    std::cout << "! This feature can't be reached for your account.\n";
}

//------------------------------------------------------------------------

bool Base_User:: set_manager_username(twitterak, std::string)
{
    std::cout << "! This feature can't be reached for your account.\n";
}
