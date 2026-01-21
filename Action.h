#pragma once
#include <string>

class Player;  

class Action {
public:
    const char kaarten[14] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'B', 'Q', 'K', 'J' };
	const int kaart_waarden[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 21 };
    Action(const std::string& name);
    virtual ~Action(); 

    virtual void execute(Player& player) = 0;

    std::string get_name();

protected:
    std::string name;
};