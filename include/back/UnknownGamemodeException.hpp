#ifndef UGE_H
#define UGE_H

#include <exception>
class UnknownGamemodeException : public std::exception
{
    const char *what() const throw(){
        return "Unknown Gamemode : It should be a number between 0 and 2.";
    }
};

#endif