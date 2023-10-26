
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "actor.hpp"
#include "diceroller.hpp"
#include "combat.hpp"
#include "json.hpp"
#include "effect.hpp"

class action
{
protected:
    std::string name;
    std::string actionType;
    std::string damageType;
    std::string saveType;
    nlohmann::json j;
    bool causeSavingThrow = false;
    int numDice, numSides, dmgBonus;
    int saveDC;
    int range;
    diceroller dice;

public:
    action(/* args */) {}
    action(std::string filename);
    virtual ~action() {}

    virtual void execute(actor &user, std::vector<std::shared_ptr<actor>> &targets, combat &battlefield) = 0; // Pure virtual function
    std::string get_name() { return name; }
    std::string get_actionType() { return actionType; }
    std::string get_damageType() { return damageType; }
    std::string get_saveType() { return saveType; }
    int get_numDice() { return numDice; }
    int get_numSides() { return numSides; }
    int get_dmgBonus() { return dmgBonus; }
    int get_saveDC() { return saveDC; }
    int get_range() { return range; }
    void set_name(std::string n) { name = n; }
    void set_actionType(std::string a) { actionType = a; }
};

class spellAction : public action
{
private:
    int spellLevel;
    int lvlCast;
    int lvlCaster;
    int duration; // in rounds

    int numTargets;
    // ... any other spell-specific properties

public:
    spellAction(/* args */) : action() {}
    spellAction(std::string filename);

    void execute(actor &user, std::vector<std::shared_ptr<actor>> &targets, combat &battlefield) override
    {
        // Implementation of spell casting on multiple targets
    }
};

class weaponAction : public action
{
private:
    bool isRanged = false;
    bool isMelee = false;

    int weaponRange;

    int numTargets;

    // ... any other weapon-specific properties

public:
    weaponAction(/* args */) : action() {}
    weaponAction(std::string filename);

    void execute(actor &user, std::vector<std::shared_ptr<actor>> &targets, combat &battlefield) override;

    void setNumTargets(int num) { numTargets = num; }
    void setWeaponRange(int range) { weaponRange = range; }
};

class moveAction : public action
{
private:
    std::pair<int, int> targetLocation;

public:
    moveAction(int x, int y) : action() { targetLocation = std::make_pair(x, y); }
    moveAction(std::pair<int, int> loc) : action() { targetLocation = loc; }
    void execute(actor &user, std::vector<std::shared_ptr<actor>> &targets, combat &battlefield) override;
};
