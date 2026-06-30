// FUNC_NAME: Entity::constructor
// Address: 0x005c0f00
// Role: Entity class constructor (EARS engine base entity)
// Global memory manager pointer DAT_012234ec is MemoryManager*

class MemoryManager; // forward decl

Entity * __thiscall Entity::constructor(Entity *this, byte flags)
{
    bool allocationSuccess;

    // Call base "Object" constructor
    Object::constructor(this);

    // Set vtable pointer (Entity's vtable)
    this->vtable = (void *)&PTR_LAB_00e3e74c;

    // If flag bit 0 is set, perform additional memory allocation
    if ((flags & 1) != 0) {
        allocationSuccess = Entity::allocateSubObjects(this); // FUN_005c43d0
        if (!allocationSuccess) {
            // Allocation failed – deallocate this object via memory manager
            // Calls MemoryManager::deallocate(this, 0) through vtable+4
            MemoryManager *memMgr = (MemoryManager *)DAT_012234ec;
            (memMgr->deallocate)(this, 0);
        }
    }

    return this;
}