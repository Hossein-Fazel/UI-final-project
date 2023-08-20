#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>
#include <QDate>

class twitterak;
class tweet;

class display
{
    public:
        void help(twitterak &);
        bool login(twitterak &,std::string , std::string);
        void login(twitterak &, std::string );
        void login(twitterak &);
        bool signup(twitterak &,std::string , std::string ,std::string ,std::string ,std::string ,QDate ,std::string ,std::string ,std::string ,std::string);

        bool signupM(twitterak &,std::string , std::string ,std::string , std::string ,std::string ,std::string ,std::string ,std::string ,std::string ,std::string);

        bool signup(twitterak &, std::string ,std::string , std::string);
        void show_tweet(twitterak,std::string, int);
        void show_tweet(twitterak,std::string);
        void show_mentions(twitterak, std::string , int);

        void show_normal(tweet);
        void show_re(tweet);
        void show_qoute(tweet);


};

#endif
