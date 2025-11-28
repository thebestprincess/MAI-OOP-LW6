#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include "../include/Visitor.h"
#include "../include/Factory.h"
#include "../include/Observer.h"

TEST(FactoryTest, CreateSquirrel)
{
    auto npc = NPCFactory::create_npc("Squirrel", 10, 20);
    EXPECT_EQ(npc->get_type(), "Squirrel");
    EXPECT_EQ(npc->x, 10);
    EXPECT_EQ(npc->y, 20);
}

TEST(FactoryTest, CreateWerewolf)
{
    auto npc = NPCFactory::create_npc("Werewolf", 0, 0);
    EXPECT_EQ(npc->get_type(), "Werewolf");
}

TEST(FactoryTest, CreateDruid)
{
    auto npc = NPCFactory::create_npc("Druid", 500, 500);
    EXPECT_EQ(npc->get_type(), "Druid");
}

TEST(FactoryTest, InvalidTypeThrows)
{
    EXPECT_THROW(NPCFactory::create_npc("Dragon", 10, 10), std::runtime_error);
}

class FightTest : public ::testing::Test
{
protected:
    std::vector<std::shared_ptr<IObserver>> observers;
};

TEST_F(FightTest, SquirrelKillsWerewolf)
{
    auto squirrel = NPCFactory::create_npc("Squirrel", 0, 0);
    auto werewolf = NPCFactory::create_npc("Werewolf", 0, 0);

    BattleVisitor v(squirrel, observers);
    werewolf->accept(v);

    EXPECT_FALSE(werewolf->is_alive);
}

TEST_F(FightTest, SquirrelKillsDruid)
{
    auto squirrel = NPCFactory::create_npc("Squirrel", 0, 0);
    auto druid = NPCFactory::create_npc("Druid", 0, 0);

    BattleVisitor v(squirrel, observers);
    druid->accept(v);

    EXPECT_FALSE(druid->is_alive);
}

TEST_F(FightTest, WerewolfKillsDruid)
{
    auto werewolf = NPCFactory::create_npc("Werewolf", 0, 0);
    auto druid = NPCFactory::create_npc("Druid", 0, 0);

    BattleVisitor v(werewolf, observers);
    druid->accept(v);

    EXPECT_FALSE(druid->is_alive);
}

TEST_F(FightTest, WerewolfVsSquirrel)
{
    auto werewolf = NPCFactory::create_npc("Werewolf", 0, 0);
    auto squirrel = NPCFactory::create_npc("Squirrel", 0, 0);

    BattleVisitor v(werewolf, observers);
    squirrel->accept(v);

    EXPECT_TRUE(squirrel->is_alive);
}

TEST_F(FightTest, DruidIsPacifist)
{
    auto druid = NPCFactory::create_npc("Druid", 0, 0);
    auto squirrel = NPCFactory::create_npc("Squirrel", 0, 0);
    auto werewolf = NPCFactory::create_npc("Werewolf", 0, 0);

    BattleVisitor v(druid, observers);
    
    squirrel->accept(v);
    werewolf->accept(v);

    EXPECT_TRUE(squirrel->is_alive);
    EXPECT_TRUE(werewolf->is_alive);
}

TEST_F(FightTest, FriendlyFireCheck)
{
    auto w1 = NPCFactory::create_npc("Werewolf", 0, 0);
    auto w2 = NPCFactory::create_npc("Werewolf", 0, 0);

    BattleVisitor v(w1, observers);
    w2->accept(v);

    EXPECT_TRUE(w2->is_alive);
}

TEST(MathTest, DistanceCheck)
{
    auto npc1 = NPCFactory::create_npc("Werewolf", 0, 0);
    auto npc2 = NPCFactory::create_npc("Werewolf", 3, 4);

    EXPECT_TRUE(npc1->is_close(*npc2, 5));
    EXPECT_FALSE(npc1->is_close(*npc2, 4));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}