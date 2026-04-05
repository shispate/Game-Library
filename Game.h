#ifndef GAME_H
#define GAME_H

#include <string>

// stores all data for a single game entry

struct Game {
    std::string title;      
    std::string publisher;   
    std::string genre;       
    float       hoursPlayed; 
    float       price;       
    short       year;        // release date year - other variables self explanatory
};

#endif // GAME_H
