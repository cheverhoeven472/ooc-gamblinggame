#pragma once
#include "Player.h"

class Dealer : public Player {
public:
    Dealer();
    ~Dealer() override;

    // Dealer specifieke functies
    void verberg_kaart();      // Verberg de eerste kaart
    void toon_kaart();         // Toon de verborgen kaart
    bool is_kaart_verborgen(); // Check of kaart verborgen is

    bool moet_hitten();

    void dealer_sequence();

   

private:
    bool kaart_verborgen = true;
};