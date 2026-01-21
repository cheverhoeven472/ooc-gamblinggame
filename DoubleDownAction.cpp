#include "DoubleDownAction.h"
#include "Player.h"
#include <iostream>

DoubleDownAction::DoubleDownAction() : Action("Double Down") {}

DoubleDownAction::~DoubleDownAction() {}

void DoubleDownAction::execute(Player& player) {
    int nieuwe_inzet = player.get_inzet() * 2;
    player.set_inzet(nieuwe_inzet);
    std::cout << player.get_name() << " verdubbelt!  Nieuwe inzet: " << nieuwe_inzet << std::endl;
}