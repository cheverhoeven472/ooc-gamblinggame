#include "DoubleDownAction.h"
#include "Player.h"
#include <iostream>
#include "HitAction.h"
#include "StandAction.h"

DoubleDownAction::DoubleDownAction() : Action("Double Down") {}

DoubleDownAction::~DoubleDownAction() {}

void DoubleDownAction::execute(Player& player) {
   
    int nieuwe_inzet = player.get_inzet() * 2;
    player.set_inzet(nieuwe_inzet);

    HitAction hit;
    hit.execute(player); 

    StandAction stand;
    stand.execute(player);  
}