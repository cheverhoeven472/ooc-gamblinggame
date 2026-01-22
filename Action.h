#pragma once
#include <string>

class Player;  

class Action {
public:
    const char kaarten[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'B', 'Q', 'K'};
	const int kaart_waarden[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    Action(const std::string& name);
    virtual ~Action(); 

    virtual void execute(Player& player) = 0;

    std::string get_name();
   
    std::string name;
};