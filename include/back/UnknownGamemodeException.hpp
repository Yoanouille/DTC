#ifndef UGE_H
#define UGE_H

#include <exception>

/**
 * Exception thrown when a gamemode is not recognized 
 */
class UnknownGamemodeException : public std::exception
{
    const char *what() const throw(){
        return "Unknown Gamemode : It should be a number between 0 and 2.";
    }
};

#endif