#ifndef MENTION_HPP
#define MENTION_HPP

#include <string>
#include <unordered_set>

#include "Tweet_Class.hpp"



class mention
{
    friend void tweet::mention_like(std::string, int);
    friend void tweet::insert_to_file(std::ofstream &write);

    public:
//======================================== sets =============================================4

        void set_userName(std::string);
        void set_name(std::string);
        void set_mention(std::string);
        void set_number(int);
        void set_likers(std::string);

//======================================== gets =============================================

        int get_number() const;
        int get_likes_number() const;
        std::string get_name() const;
        std::string get_username() const;
        std::string get_mention() const;
        std::unordered_set<std::string> operator~() const;

    private:
        std::string mUsername;
        std::string mName;
        std::string mention;
        int mNumber;
        std::unordered_set<std::string> mLikes;
};


#endif
