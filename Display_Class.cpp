#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <QMessageBox>
#include <QDate>

#include "Display_Class.hpp"
#include "Twitterak_Class.hpp"
#include "sha256.h"

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
