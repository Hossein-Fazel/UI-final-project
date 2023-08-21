#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>
#include <QDate>

class twitterak;
class tweet;

class display
{
    public:
        bool login(twitterak &,std::string , std::string);
        bool signup(twitterak &,std::string , std::string ,std::string ,std::string ,std::string ,QDate ,std::string ,std::string ,std::string ,std::string);
        bool signupM(twitterak &,std::string , std::string ,std::string , std::string ,std::string ,std::string ,std::string ,std::string ,std::string ,std::string);
        bool signup(twitterak &, std::string ,std::string , std::string);
};

#endif
