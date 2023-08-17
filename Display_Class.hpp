#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>


class twitterak;
class tweet;

class display
{
    public:
        void help(twitterak &);
        bool login(twitterak &,std::string , std::string);
        void login(twitterak &, std::string );
        void login(twitterak &);
        bool signup(twitterak &,std::string Aname, std::string Ausername,std::string Apassword,std::string bio,std::string country,std::string birth,std::string phone,std::string link,std::string color);

        bool signupM(twitterak &,std::string Aname, std::string Ausername,std::string Apassword, std::string manager,std::string bio,std::string country,std::string phone,std::string link,std::string color);

        bool signup(twitterak &, std::string Ausername,std::string Apassword);
        void show_tweet(twitterak,std::string, int);
        void show_tweet(twitterak,std::string);
        void show_mentions(twitterak, std::string user_name, int tweet_number);

        void show_normal(tweet);
        void show_re(tweet);
        void show_qoute(tweet);


};

#endif
