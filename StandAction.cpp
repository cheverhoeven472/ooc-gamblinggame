#include "StandAction.h"
#include "Player.h"
#include <iostream>

StandAction::StandAction() : Action("Stand") {}

StandAction::~StandAction() {}

void StandAction::execute(Player& player) {
    std::cout << player.get_name() << " past!" << std::endl;
    // Speler is klaar met zijn beurt
}