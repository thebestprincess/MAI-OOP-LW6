#ifndef ARENA_H
#define ARENA_H

#include "NPC.h"
#include "Observer.h"
#include <memory>
#include <vector>

class Arena final
{
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<IObserver>> observers;

    Arena();

public:
    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;
    static Arena& get_instance();

    void add_npc(const std::string& type, int x, int y);
    void save_to_file(const std::string& filename);
    void load_from_file(const std::string& filename);
    void print_survivors();
    void battle(size_t distance);
};

#endif // ARENA_H