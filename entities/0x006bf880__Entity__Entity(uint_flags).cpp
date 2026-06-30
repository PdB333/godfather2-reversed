// FUNC_NAME: Entity::Entity(uint flags)

// 0x006bf880: Constructor for Entity base class (size 0x190)
// flags: bit 0 = 1 indicates heap allocation (via operator new), 
//         0 indicates stack/placement allocation.
// Calls init() to set default state, then if heap-allocated,
// registers memory with the engine's memory manager.
int __thiscall Entity::Entity(Entity* this, byte flags)
{
    // Default initialization (clears fields, sets vtable, etc.)
    FUN_006bf7e0(this);
    
    // If the object was allocated on the heap, register the allocation
    // with the memory manager (FUN_0043b960 expects pointer and size 0x190).
    if (flags & 1)
    {
        FUN_0043b960(this, 400); // 0x190 = 400 bytes
    }
    
    return this;
}