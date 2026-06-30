// FUNC_NAME: Entity::Entity
// Function address: 0x00541970
// Role: Constructor for Entity class. Calls base constructor (FUN_005419a0) and optionally invokes a virtual function from a global vtable if param_2 bit 0 is set.

// Note: DAT_01223410 is a global pointer to a large structure (likely gEngine or gGameManager).
// Offset 0x2d4 from that structure points to a vtable or class descriptor.
// The virtual function at index 1 (offset +4 from vtable) is called with (this, 0) when param_2 & 1 is true.

Entity* __thiscall Entity::Entity(Entity* this, byte param_2)
{
    // Call base class constructor (likely BaseEntity or SimObject)
    BaseEntity::BaseEntity(this);  // FUN_005419a0

    // If param_2 has bit 0 set, invoke a virtual initialization function
    if ((param_2 & 1) != 0)
    {
        // Dereference global pointer + 0x2d4 to get a vtable pointer
        // Then call the second virtual function (offset +4) with this and 0
        void** vtable = *(void***)(*(int*)DAT_01223410 + 0x2d4);
        ((void(__thiscall*)(Entity*, int))vtable[1])(this, 0);
    }

    return this;
}