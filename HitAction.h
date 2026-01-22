#pragma once
#include "Action.h"

class HitAction : public Action {  
public:
    HitAction();
    ~HitAction() override;

    void execute(Player& player) override;  
};