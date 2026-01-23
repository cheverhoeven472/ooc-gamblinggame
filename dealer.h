#pragma once
#include "Player.h"

class Dealer : public Player {
public:
    Dealer();
    ~Dealer() override;

    // Dealer specifieke functies
    void verberg_kaart();     
    void toon_kaart();        
    bool is_kaart_verborgen();
    bool Dealer_busted;

    bool moet_hitten();

    void dealer_sequence();

   

private:
    bool kaart_verborgen = true;
};