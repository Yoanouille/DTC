#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player
{
    protected:
        std::string const name;
        int score;
        static int num;

    public:
        Player(std::string n);
        virtual ~Player();
        std::string getName() const;
        int getScore() const;
        void addScore(int);
};

#endif