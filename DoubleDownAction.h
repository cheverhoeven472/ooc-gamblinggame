#pragma once
#include "Action.h"

class DoubleDownAction : public Action {
public:
    DoubleDownAction();
    ~DoubleDownAction() override;

    void execute(Player& player) override;
};