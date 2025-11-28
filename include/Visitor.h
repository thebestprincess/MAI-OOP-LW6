#ifndef VISITOR_H
#define VISITOR_H

#include "NPC.h"
#include "Observer.h"
#include <memory>
#include <vector>

class NPCVisitor
{
public:
    virtual void visit(Squirrel& squirrel) = 0;
    virtual void visit(Werewolf& werewolf) = 0;
    virtual void visit(Druid& druid) = 0;
    virtual ~NPCVisitor() = default;
};

class BattleVisitor final: public NPCVisitor
{
    std::shared_ptr<NPC> attacker;
    std::vector<std::shared_ptr<IObserver>>& observers;
    
public:
    BattleVisitor(std::shared_ptr<NPC> attacker, std::vector<std::shared_ptr<IObserver>>& observers);
    ~BattleVisitor() = default;

    void notify(const std::string& victim_type) const;

    void visit(Squirrel& defender) override;
    void visit(Werewolf& defender) override;
    void visit(Druid& defender) override;
};

#endif // VISITOR_H