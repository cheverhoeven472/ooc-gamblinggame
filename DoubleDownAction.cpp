#include "DoubleDownAction.h"
#include "Player.h"
#include <iostream>
#include "HitAction.h"
#include "StandAction.h"

DoubleDownAction::DoubleDownAction() : Action("Double Down") {}

DoubleDownAction::~DoubleDownAction() {}

void DoubleDownAction::execute(Player& player) {
    // Verdubbel inzet
    int nieuwe_inzet = player.get_inzet() * 2;
    player.set_inzet(nieuwe_inzet);
    std::cout << player.get_name() << " verdubbelt! Nieuwe inzet: " << nieuwe_inzet << std::endl;

    // Maak objecten aan en voer uit
    HitAction hit;
    hit.execute(player); 

    StandAction stand;
    stand.execute(player);  
}