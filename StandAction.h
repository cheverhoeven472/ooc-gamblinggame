#pragma once
#include "Action.h"

class StandAction : public Action {
    public:
    StandAction();
    ~StandAction() override;

    void execute(Player& player) override;
};