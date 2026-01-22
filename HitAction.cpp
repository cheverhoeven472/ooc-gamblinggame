#include "HitAction.h"
#include "Player.h"
#include <iostream>
#include <random>

HitAction::HitAction() : Action("Hit") {}

HitAction::~HitAction() {}

const char AAS = 'A';

void HitAction::execute(Player& player) {
    // 1. Trek random kaart
    int random_getal = rand() % 13;

    // 2. Voeg kaart toe aan hand
    player.Player_kaart[player.kaart_index] = kaarten[random_getal];
    player.kaart_index += 1;

    // 3. Bereken hand waarde opnieuw (met aas logica)
    int hand_waarde = 0;
    int aantal_azen = 0;

    // Tel eerst alle kaarten op (aas = 1)
    for (int i = 0; i < player.kaart_index; i++) {
        if (player.Player_kaart[i] == AAS) {
            hand_waarde += 1;  // Aas telt eerst als 1
            aantal_azen += 1;
        }
        else {
            // Zoek de waarde van de kaart
            for (int j = 0; j < 13; j++) {
                if (player.Player_kaart[i] == kaarten[j]) {
                    hand_waarde += kaart_waarden[j];
                    break;
                }
            }
        }
    }

    // Maak azen 11 waard als dat kan (zonder bust te gaan)
    for (int i = 0; i < aantal_azen; i++) {
        if (hand_waarde + 10 <= 21) {
            hand_waarde += 10;  // Maak aas 11 in plaats van 1
        }
    }

    player.set_hand_value(hand_waarde);

    std::cout << player.get_name() << " neemt een kaart:  " << kaarten[random_getal] << std::endl;
}