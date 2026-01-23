#pragma once
#include "Action.h"

class HitAction : public Action {  
public:
    HitAction();
    ~HitAction() override;

    void starting_hand(Player& player);

    void execute(Player& player) override;  
};