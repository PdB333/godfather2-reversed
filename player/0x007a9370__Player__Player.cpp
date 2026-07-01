// FUNC_NAME: Player::Player

#include <cstdint>

// Forward declarations for base class and memory allocator
class Entity; // Base class (FUN_007a7030 likely Entity constructor)
extern void __thiscall Entity_constructor(Entity* this); // Actual base constructor
extern void __fastcall AllocateMemory(void* this, uint32 size); // FUN_0043b960 - EARS memory allocator

// Player class constructor
uint32 __thiscall Player::Player(uint8 allocFlag)
{
    // Invoke base class constructor (Entity or Sentient)
    Entity_constructor(reinterpret_cast<Entity*>(this));

    // If the low bit of allocFlag is set, allocate a large internal data block (0x31D0 = 12752 bytes)
    if ((allocFlag & 1) != 0)
    {
        AllocateMemory(this, 0x31D0);
    }

    return reinterpret_cast<uint32>(this);
}