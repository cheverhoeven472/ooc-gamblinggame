#include "Dealer.h"
#include "HitAction.h"
#include <iostream>

Dealer::Dealer() : Player("Dealer", 0) {}

Dealer::~Dealer() {}

void Dealer::verberg_kaart() {
    kaart_verborgen = true;
}

void Dealer::toon_kaart() {
    kaart_verborgen = false;
}

bool Dealer::is_kaart_verborgen() {
    return kaart_verborgen;
}

bool Dealer::moet_hitten() {
    // Dealer MOET hitten bij 16 of lager
    // Dealer MOET stoppen bij 17 of hoger
    return get_hand_value() < 17;
}

void Dealer::dealer_sequence() {
    static HitAction hit;
    
    // 1. Toon de verborgen kaart
    toon_kaart();
    
    
    // 2. Dealer hit tot 17 of hoger
    while (moet_hitten()) {
        hit.execute(*this);  
    }
    
    // 3. Dealer stopt
    if (get_hand_value() > 21) {
		Dealer_busted = true;
    } 
    
    set_stood(true);
}

     