#include "player.h"
#include <string>

Player::Player(const std::string& name, int PlayerNumber) {
	Player::set_name(name);
	Player::playerNumber = PlayerNumber;
}

Player:: ~Player()
{
}

void Player::set_inzet(int inzet) {
	Player::inzet = inzet;
}

void Player::set_hand_value(int value) {
	Player::hand_value = value;
}

void Player::set_name(const std::string& name) {
	Player::name = name;
}

std::string Player::get_name() {
	return Player::name;
}

int Player::get_inzet() {
	return Player::inzet;
}

int Player::get_hand_value() {
	return Player::hand_value;
}