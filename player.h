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
	char Player_kaart[10];
	int kaart_index = 0;
	void set_stood(bool value);
	bool has_stood();
	bool stood = false;
	std::string name;
	int inzet;
	int hand_value;
};