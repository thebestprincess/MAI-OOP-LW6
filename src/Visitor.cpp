#include "../include/Visitor.h"

BattleVisitor::BattleVisitor(std::shared_ptr<NPC> attacker, std::vector<std::shared_ptr<IObserver>>& observers)
    : attacker(attacker), observers(observers) {}

void BattleVisitor::notify(const std::string& victim_type) const
{
    for (auto& obs : observers)
    {
        obs->on_kill(attacker->get_type(), victim_type);
    }
}

void BattleVisitor::visit(Squirrel& defender) {}

void BattleVisitor::visit(Werewolf& defender)
{
    if (attacker->get_type() == "Squirrel")
    {
        defender.is_alive = false;
        notify(defender.get_type());
    }
}

void BattleVisitor::visit(Druid& defender)
{
    if (attacker->get_type() == "Squirrel" || attacker->get_type() == "Werewolf")
    {
        defender.is_alive = false;
        notify(defender.get_type());
    }
}
