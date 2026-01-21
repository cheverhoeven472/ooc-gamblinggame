#pragma once
#include <string>

class Player {
public:
	int playerNumber;
	Player(const std::string& name, int PlayerNumber);
	virtual ~Player();
	void set_inzet(int inzet);
	void set_hand_value(int value);
	void set_name(const std::string& name);
	std::string get_name();
	int get_inzet();
	int get_hand_value();
private:
	std::string name;
	int inzet;
	int hand_value;
};