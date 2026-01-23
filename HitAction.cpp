#include "HitAction.h"
#include "Player.h"
#include <iostream>
#include <random>

HitAction::HitAction() : Action("Hit") {}

HitAction::~HitAction() {}

const char AAS = 'A';

void HitAction::starting_hand(Player& player)
{
	int hand_waarde_2 = 0;
    for (int j = 0; j < 2; j++) {
		int random_getal = rand() % 13;
		player.Player_kaart[player.kaart_index] = kaarten[random_getal];
        if (player.Player_kaart[player.kaart_index] == AAS) {
            hand_waarde_2 += 11;  
        }
        else {
            for (int k = 0; k < 13; k++) {
                if (player.Player_kaart[player.kaart_index] == kaarten[k]) {
                    hand_waarde_2 += kaart_waarden[k];
                    break;
                }
            }
		}
		player.set_hand_value(hand_waarde_2);
		player.kaart_index += 1;
    }
}

void HitAction::execute(Player& player) {
 
    int random_getal = rand() % 13;


    player.Player_kaart[player.kaart_index] = kaarten[random_getal];
    player.kaart_index += 1;


    int hand_waarde = 0;
    int aantal_azen = 0;


    for (int i = 0; i < player.kaart_index; i++) {
        if (player.Player_kaart[i] == AAS) {
            hand_waarde += 1;  // Aas telt eerst als 1
            aantal_azen += 1;
        }
        else {

            for (int j = 0; j < 13; j++) {
                if (player.Player_kaart[i] == kaarten[j]) {
                    hand_waarde += kaart_waarden[j];
                    break;
                }
            }
        }
    }


    for (int i = 0; i < aantal_azen; i++) {
        if (hand_waarde + 10 <= 21) {
            hand_waarde += 10;  // Maak aas 11 in plaats van 1
        }
    }

    player.set_hand_value(hand_waarde);

}