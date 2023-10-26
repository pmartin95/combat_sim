#include "action.hpp"

action::action(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file " + filename);
    }
    file >> j;
    file.close();
    try
    {
        // string elements
        name = utility::validateJSONStringElement(j, "name");
        actionType = utility::validateJSONStringElement(j, "actionType");
        damageType = utility::validateJSONStringElement(j, "damageType");
        saveType = utility::validateJSONStringElement(j, "saveType");

        // boolean elements
        causeSavingThrow = utility::validateJSONBoolean(j, "causeSavingThrow");

        // integral elements
        numDice = utility::validateJSONIntegralElement(j, "numDice");
        numSides = utility::validateJSONIntegralElement(j, "numSides");
        dmgBonus = utility::validateJSONIntegralElement(j, "dmgBonus");
        saveDC = utility::validateJSONIntegralElement(j, "saveDC");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

spellAction::spellAction(std::string filename) : action(filename)
{
    spellLevel = utility::validateJSONIntegralElement(j, "spellLevel");
    lvlCast = utility::validateJSONIntegralElement(j, "lvlCast");
    lvlCaster = utility::validateJSONIntegralElement(j, "lvlCaster");
    duration = utility::validateJSONIntegralElement(j, "duration");
    range = utility::validateJSONIntegralElement(j, "range");
    numTargets = utility::validateJSONIntegralElement(j, "numTargets");
}

void weaponAction::execute(actor &user, std::vector<std::shared_ptr<actor>> &targets, combat &battlefield)
{
    // Implementation of weapon attack on multiple targets
    try
    {
        if (targets.size() > numTargets)
        {
            throw std::invalid_argument("Too many targets for this action");
        }
        for (int i = 0; i < numTargets; i++)
        {
            int dmg = dice.roll(numDice, numSides) + dmgBonus;
            targets[i]->take_damage(dmg, damageType);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

weaponAction::weaponAction(std::string filename) : action(filename)
{
    weaponRange = utility::validateJSONIntegralElement(j, "weaponRange");
    dmgBonus = utility::validateJSONIntegralElement(j, "damageBonus");
    numTargets = utility::validateJSONIntegralElement(j, "numTargets");
}

void moveAction::execute(actor &user, std::vector<std::shared_ptr<actor>> &targets, combat &battlefield)
{
    // Implementation of movement
    try
    {
        if (targets.size() > 0)
        {
            throw std::invalid_argument("Too many targets for this action");
        }
        if (user.get_location() == targetLocation)
        {
            throw std::invalid_argument("Already at target location");
        }
        // test distance
        int x1 = user.get_location().first;
        int y1 = user.get_location().second;
        int x2 = targetLocation.first;
        int y2 = targetLocation.second;
        int distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        if (distance > user.get_speed())
        {
            throw std::invalid_argument("Target location is too far away");
        }
        user.set_location(targetLocation);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}