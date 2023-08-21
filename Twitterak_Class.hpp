#ifndef TWITTERAK_HPP
#define TWITTERAK_HPP

#include "User_Class.hpp"
#include "Tweet_Class.hpp"
#include "Display_Class.hpp"
#include "Base_User.hpp"
#include "Organisation_User.hpp"
#include "Anonymous_User.hpp"

#include <unordered_map>
#include <vector>
#include <string>
#include <QDate>

class mention;

class twitterak
{
//=================== Friends ===================
friend void user::follow(twitterak &, std::string);
friend bool display::login(twitterak  &,std::string, std::string);
friend bool display::signup(twitterak &, std::string Ausername, std::string Apassword, std::string);
friend bool display::signup(twitterak &, std::string, std::string, std::string, std::string,
                            std::string, QDate, std::string, std::string, std::string, std::string);
friend bool display::signupM(twitterak &, std::string, std::string, std::string, std::string, std::string,
                             std::string, std::string, std::string, std::string, std::string);
friend void tweet::fetch_hashtags(twitterak &);                           // friend with Twitterak_Class to fecth hashtags from tweets

friend bool Organisation::set_manager_username(twitterak &,std::string);
    public:
        display d1;
        twitterak();
        void put_users();
        void read_users();
        std::string lower(std::string);
        void read_from_file();                                              // read tweets and mentions from a text file

        std::unordered_map<std::string, user> get_users();
        std::unordered_map<std::string, Organisation> get_org();
        std::unordered_map<std::string, Anonymous> get_ans();
        std::unordered_map<std::string, std::vector<tweet>> get_hashtags();

    private:
        Base_User *li_user;
        bool is_logedin = false;
        std:: string logedin_user;
        
        std::vector<std::string> commands; 
        std::unordered_map<std::string, user> users;
        std::unordered_map<std::string, Organisation> org_user;
        std::unordered_map<std::string, Anonymous> ans_user;
        std::unordered_map<std::string,std::vector<tweet>> Hashtags;
};

#endif
