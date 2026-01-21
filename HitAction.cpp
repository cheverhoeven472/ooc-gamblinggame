#include "HitAction.h"
#include "Player.h"
#include <iostream>

HitAction::HitAction() : Action("Hit") {}  // ← Roept basis constructor aan

HitAction::~HitAction() {}

void HitAction::execute(Player& player) {
    std::cout << player.get_name() << " neemt een kaart!" << std::endl;
    
}