#ifndef NPC_H
#define NPC_H

#include <string>

class NPCVisitor;

class NPC
{
public:
    int x;
    int y;
    bool is_alive = true;

public:
    NPC(int x, int y);
    virtual ~NPC() = default;

    virtual void accept(NPCVisitor& visitor) = 0;
    virtual std::string get_type() const = 0;
    bool is_close(const NPC& other, size_t distance) const;
};

class Squirrel final: public NPC
{
public:
    Squirrel(int x, int y);
    ~Squirrel() = default;

    void accept(NPCVisitor& visitor) override;
    std::string get_type() const override;
};

class Werewolf final: public NPC
{
public:
    Werewolf(int x, int y);
    ~Werewolf() = default;

    void accept(NPCVisitor& visitor) override;
    std::string get_type() const override;
};

class Druid final: public NPC
{
public:
    Druid(int x, int y);
    ~Druid() = default;

    void accept(NPCVisitor& visitor) override;
    std::string get_type() const override;
};

#endif // NPC_H