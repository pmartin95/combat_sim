#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "actor.hpp"
#include "diceroller.hpp"
#include "combat.hpp"
#include "json.hpp"
#include "effect.hpp"
#include "action.hpp"
#include "utility.hpp"

class actor;
class effect;
class combat;
class diceroller;
// default strategy is to select nearest enemy and use highest dpr action
class strategy
{
protected:
    std::shared_ptr<actor> nearestEnemy;
    std::shared_ptr<action> highestDPRAction;
    std::vector<std::shared_ptr<action>> actions;

public:
    strategy(/* args */){};
    strategy(actor &user){};
    strategy(actor &user, combat &battlefield){};
    virtual ~strategy(){};

    void detectNearestEnemy(actor &user, combat &battlefield);
    void detectHighestDPRAction(actor &user, actor &target);
    int calculateDistance(actor &user, actor &target);
    int calculateDPR(actor &user, actor &target, action &actionInstance);
    void formulatePlan(actor &user, combat &battlefield);

    std::vector<std::shared_ptr<action>> get_actions() { return actions; }
    std::shared_ptr<actor> get_nearestEnemy() { return nearestEnemy; }
};