#include "StandAction.h"
#include "Player.h"
#include <iostream>

StandAction::StandAction() : Action("Stand") {}

StandAction::~StandAction() {}

void StandAction::execute(Player& player) {
    player.set_stood(true);  // ← Zet stood op true
    std::cout << player.get_name() << " past!" << std::endl;
}