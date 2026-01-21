#pragma once
#include "Action.h"

class HitAction : public Action {  // ← Erft over van Action
public:
    HitAction();
    ~HitAction() override;

    void execute(Player& player) override;  // ← Implementeert de pure virtual
};