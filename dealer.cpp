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
    std::cout << "Dealer toont verborgen kaart!" << std::endl;
    
    // 2. Dealer hit tot 17 of hoger
    while (moet_hitten()) {
        std::cout << "Dealer heeft " << get_hand_value() << ", moet hitten..." << std::endl;
        hit.execute(*this);  // ← *this = dit Dealer object (is ook een Player)
    }
    
    // 3. Dealer stopt
    if (get_hand_value() > 21) {
        std::cout << "Dealer BUST met " << get_hand_value() << "!" << std::endl;
    } else {
        std::cout << "Dealer stopt met " << get_hand_value() << std::endl;
    }
    
    set_stood(true);
}
/*
void Dealer::reset() {
    kaart_verborgen = true;
    kaart_index = 0;
    set_hand_value(0);
    set_stood(false);
}
    */ 