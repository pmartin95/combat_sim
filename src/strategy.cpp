#include "strategy.hpp"
void strategy::detectNearestEnemy(actor &user, combat &battlefield)
{
    // std::cout << "Detecting nearest enemy" << std::endl;
    int minDistance = 1000;
    int distance = 0;
    std::string targetUUID;
    for (auto &target : battlefield.get_actors())
    {
        if (target->get_team() != user.get_team())
        {
            distance = utility::distance(user.get_location(), target->get_location());
            if (distance < minDistance)
            {
                minDistance = distance;
                targetUUID = target->get_combat_hash();
            }
        }
    }

    nearestEnemy = battlefield.get_actor_by_uuid(targetUUID);
}
void strategy::detectHighestDPRAction(actor &user, actor &target)
{
    // std::cout << "Detecting highest DPR action" << std::endl;
    int maxDPR = 0;
    int DPR = 0;
    for (auto &action : user.get_actions())
    {
        DPR = calculateDPR(user, target, *action);
        if (DPR > maxDPR)
        {
            maxDPR = DPR;
            highestDPRAction = action;
        }
    }
}

int strategy::calculateDPR(actor &user, actor &target, action &actionInstance)
{
    int numDice = actionInstance.get_numDice();
    int numSides = actionInstance.get_numSides();
    int dmgBonus = actionInstance.get_dmgBonus();
    int avgDmg = ((numSides + 1) * numDice / 2) + dmgBonus;
    if (utility::vectorContainsString(target.get_dmg_resistances(), actionInstance.get_damageType()))
    {
        avgDmg /= 2;
    }
    else if (utility::vectorContainsString(target.get_dmg_vulnerabilities(), actionInstance.get_damageType()))
    {
        avgDmg *= 2;
    }
    else if (utility::vectorContainsString(target.get_dmg_immunities(), actionInstance.get_damageType()))
    {
        avgDmg = 0;
    }
    return avgDmg;
}

void strategy::formulatePlan(actor &user, combat &battlefield)
{
    actions.clear();
    detectNearestEnemy(user, battlefield);
    detectHighestDPRAction(user, *nearestEnemy);
    int distance = utility::distance(user.get_location(), nearestEnemy->get_location());
    int actionRange = highestDPRAction->get_range();
    if (distance <= actionRange)
    {
        actions.push_back(highestDPRAction);
        actions.back()->set_actionType("attack");
    }
    else if (distance - actionRange <= user.get_speed())
    {
        // calculate coordinates to land on so one off of enemy
        int x1 = user.get_location().first;
        int x2 = nearestEnemy->get_location().first;
        int dx = x2 - x1;
        int x3 = x1 + dx;
        if (dx < 0)
        {
            x3 += actionRange;
        }
        else
        {
            x3 -= actionRange;
        }
        int y3 = nearestEnemy->get_location().second;
        actions.push_back(std::shared_ptr<action>(new moveAction(x3, y3)));
        actions.back()->set_actionType("move");
        actions.push_back(highestDPRAction);
        actions.back()->set_actionType("attack");
    }
    else
    {
        int x1 = user.get_location().first / 5;
        int x2 = nearestEnemy->get_location().first / 5;
        int dx = x2 - x1;
        int y1 = user.get_location().second / 5;
        int y2 = nearestEnemy->get_location().second / 5;
        int dy = y2 - y1;
        int distance = utility::distance(user.get_location(), nearestEnemy->get_location()) / 5;
        int x3 = dx / distance * user.get_speed() * 5;
        int y3 = dy / distance * user.get_speed() * 5;

        // move towards enemy
        actions.push_back(std::shared_ptr<action>(new moveAction(x3, y3)));
        actions.back()->set_actionType("move");
    }
}