#include "Action.h"

Action::Action(const std::string& name) : name(name) {}

Action::~Action() {}

std::string Action::get_name() {
    return name;
}   