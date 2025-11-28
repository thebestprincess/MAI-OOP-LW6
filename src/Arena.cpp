#include "../include/Arena.h"

#include "../include/Factory.h"
#include "../include/Visitor.h"
#include <fstream>

Arena::Arena()
{
    observers.push_back(std::make_shared<ConsoleObserver>());
    observers.push_back(std::make_shared<FileObserver>());
}

Arena& Arena::get_instance()
{
    static Arena instance;
    return instance;
}

void Arena::add_npc(const std::string& type, int x, int y)
{
    npcs.push_back(NPCFactory::create_npc(type, x, y));
}

void Arena::save_to_file(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file for save\n";
        return;
    }
    for (const auto& npc : npcs)
    {
        if (npc->is_alive)
        {
            file << npc->get_type() << " " << npc->x << " " << npc->y << std::endl;
        }   
    }
    std::cout << "Saved to " << filename << std::endl;
}

void Arena::load_from_file(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file for load\n";
        return;
    }
    
    npcs.clear();
    std::string type;
    int x;
    int y;

    while(file >> type >> x >> y)
    {
        try
        {
            add_npc(type, x, y);
        }
        catch(...)
        {
            std::cerr << "Skipping invalid NPC...\n";
        }
    }

    std::cout << "Loaded from file " << filename << std::endl;
}

void Arena::print_survivors()
{
    std::cout << "----- NPC List (" << npcs.size() << ") -----\n";
    for (const auto& npc : npcs)
    {
        if (npc->is_alive)
        {
            std::cout << npc->get_type() << " [" << npc->x << ", " << npc->y << "]\n";
        }
    }
}

void Arena::battle(size_t distance)
{
    std::cout << "\n--- Battle Range: " << distance << "m ---\n";

    size_t range = 10;

    while (range <= distance)
    {
        print_survivors();

        for (auto& attacker : npcs)
        {
            for (auto& defender : npcs)
            {
                if (attacker == defender) continue;
                if (!attacker->is_alive || !defender->is_alive) continue;
                
                if (attacker->is_close(*defender, range))
                {
                    BattleVisitor visitor(attacker, observers);
                    defender->accept(visitor);
                }
            }
        }

        range += 50;
    }

    save_to_file("../result.txt");
}
