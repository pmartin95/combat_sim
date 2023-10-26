#pragma once
#include <string>
#include <random>
#include <fstream>
#include <algorithm>
#include <map>
#include <memory>
#include "json.hpp"
#include "diceroller.hpp"
#include "action.hpp"
#include "utility.hpp"
#include "strategy.hpp"
#include "combat.hpp"

class action;
class combat;
class diceroller;
class effect;
class strategy;

class actor
{
private:
    /* data */
    std::string name, status, combat_hash; // combat_hash is a unique identifier for the actor in combat
    std::string actorClass, race, background, alignment;
    int max_hp, current_hp;
    std::shared_ptr<strategy> strategy_instance;

    int initiative;
    int ac;
    int targetAlignment;

    std::map<std::string, int> stats = {{"str", 10}, {"dex", 10}, {"con", 10}, {"int", 10}, {"wis", 10}, {"cha", 10}};
    std::map<std::string, int> stats_mod = {{"str", 0}, {"dex", 0}, {"con", 0}, {"int", 0}, {"wis", 0}, {"cha", 0}};
    std::map<std::string, bool> stats_save_prof = {{"str", false}, {"dex", false}, {"con", false}, {"int", false}, {"wis", false}, {"cha", false}};
    std::map<std::string, int> stats_save = {{"str", 0}, {"dex", 0}, {"con", 0}, {"int", 0}, {"wis", 0}, {"cha", 0}};
    std::vector<std::string> skills, senses, languages;
    std::vector<std::string> dmg_vulnerabilities, dmg_resistances, dmg_immunities, condition_immunities;
    std::vector<std::shared_ptr<action>> actions;
    int location[2] = {0}; // [x, y]
    diceroller dice;
    int speed = 30;
    int passive_perception;
    int proficiency_bonus = 0;
    int inspiration;
    int level;
    int xp;
    void calc_mods();
    void calc_saves();

public:
    actor(/* args */);
    actor(std::string filename);
    ~actor();
    void inputstats(const int (&stats_in)[6]);
    void inputstats(const std::map<std::string, int> &stats_in);
    void rollInitiative();
    int rollSavingThrow(std::string stat);
    void assign_combat_hash(std::string hash);
    void add_action(std::shared_ptr<action> new_action);
    void add_skill(std::string skill);
    void perform_action(std::string action_name, std::vector<actor *> targets);
    void take_damage(int dmg, std::string dmg_type);
    void restoreHealth();
    void make_strategy(combat &combat_instance);
    void make_actions(combat &combat_instance);

    // Get methods
    std::string get_name() { return name; }
    std::string get_combat_hash();
    std::string get_status() { return status; }
    std::string get_actorClass() { return actorClass; }
    std::string get_race() { return race; }
    std::string get_background() { return background; }
    std::string get_alignment() { return alignment; }
    std::vector<std::string> &get_dmg_vulnerabilities() { return dmg_vulnerabilities; }
    std::vector<std::string> &get_dmg_resistances() { return dmg_resistances; }
    std::vector<std::string> &get_dmg_immunities() { return dmg_immunities; }
    std::vector<std::string> &get_condition_immunities() { return condition_immunities; }
    std::vector<std::shared_ptr<action>> &get_actions() { return actions; }
    int get_max_hp() { return max_hp; }
    int get_current_hp() { return current_hp; }
    int get_initiative() { return initiative; }
    int get_ac() { return ac; }
    int get_team() { return targetAlignment; }
    std::map<std::string, int> get_stats() { return stats; }
    std::map<std::string, int> get_stats_mod() { return stats_mod; }
    std::map<std::string, bool> get_stats_save_prof() { return stats_save_prof; }
    std::map<std::string, int> get_stats_save() { return stats_save; }
    std::vector<std::string> get_skills() { return skills; }
    int get_speed() { return speed; }
    int get_passive_perception() { return passive_perception; }
    int get_proficiency_bonus() { return proficiency_bonus; }
    int get_inspiration() { return inspiration; }
    int get_level() { return level; }
    int get_xp() { return xp; }
    std::pair<int, int> get_location() { return std::make_pair(location[0], location[1]); }
    std::vector<std::shared_ptr<action>> &get_actions_shared() { return actions; }
    // Set methods
    void set_name(std::string val) { name = val; }
    void set_status(std::string val) { status = val; }
    void set_combat_hash(std::string val) { combat_hash = val; }
    void set_actorClass(std::string val) { actorClass = val; }
    void set_race(std::string val) { race = val; }
    void set_background(std::string val) { background = val; }
    void set_alignment(std::string val) { alignment = val; }
    void set_max_hp(int val) { max_hp = val; }
    void set_current_hp(int val) { current_hp = val; }
    void set_initiative(int val) { initiative = val; }
    void set_ac(int val) { ac = val; }
    void set_stats(std::map<std::string, int> val)
    {
        stats = val;
        calc_mods();
    }
    void set_location(int x, int y)
    {
        location[0] = x;
        location[1] = y;
    }
    void set_location(std::pair<int, int> loc)
    {
        location[0] = loc.first;
        location[1] = loc.second;
    }
    void set_stats_save_prof(std::map<std::string, bool> val)
    {
        stats_save_prof = val;
        calc_saves();
    }
    void set_skills(std::vector<std::string> val) { skills = val; }
    void set_speed(int val) { speed = val; }
    void set_passive_perception(int val) { passive_perception = val; }
    void set_proficiency_bonus(int val)
    {
        proficiency_bonus = val;
        calc_mods();
        calc_saves();
    }
    void set_inspiration(int val) { inspiration = val; }
    void set_level(int val) { level = val; }
    void set_xp(int val) { xp = val; }
    void set_targetAlignment(int val) { targetAlignment = val; }
};
