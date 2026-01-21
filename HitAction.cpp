#include "HitAction.h"
#include "Player.h"
#include <iostream>
#include <random>

HitAction::HitAction() : Action("Hit") {}  // ← Roept basis constructor aan

HitAction::~HitAction() {}

void HitAction::execute(Player& player) {
    int random_getal = rand() % 13; // Genereer een willekeurig getal tussen 0 en 13 

    player.set_hand_value(player.get_hand_value() + kaart_waarden[random_getal]);
    player.Player_kaart[player.kaart_index] = kaarten[random_getal];
	player.kaart_index += 1;
    
    std::cout << player.get_name() << " neemt een kaart!" << std::endl;
}