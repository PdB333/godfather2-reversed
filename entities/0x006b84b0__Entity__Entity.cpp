// FUNC_NAME: Entity::Entity
// Address: 0x006b84b0
// Constructor for Entity class. Initializes multiple inheritance vtables and a sub-object at offset 0x14.

class Entity {
public:
    void **vtable; // +0x00: primary vtable
    // unknown members up to offset 0x14
    // SomeList m_someList; // +0x14: internal container (list/vector)
    // at offset 0x3C: void *secondaryVtable1;
    // at offset 0x48: void *secondaryVtable2;
    // total size assumed 0x68 (104 bytes)
};

// Constructor with flag for special initialization
void __thiscall Entity::Entity(Entity *this, byte creationFlag)
{
    // Set primary vtable
    this->vtable = (void **)&PTR_FUN_00d5e5b8;

    // Set secondary vtable pointers (multiple inheritance)
    *(void **)((uintptr_t)this + 0x3C) = (void *)&PTR_LAB_00d5e5a8; // +0x3C
    *(void **)((uintptr_t)this + 0x48) = (void *)&PTR_LAB_00d5e5a4; // +0x48

    // Initialize the internal list/container at offset 0x14
    // List constructor + clear
    FUN_004086d0((void *)((uintptr_t)this + 0x14)); // Construct list
    FUN_00408310((void *)((uintptr_t)this + 0x14)); // Clear list

    // Global initialization (likely object registration or singleton setup)
    FUN_0046c640();

    // Conditional cleanup based on creationFlag
    if ((creationFlag & 1) != 0) {
        // If flag bit 1 set, deallocate object (size 0x68)
        FUN_0043b960(this, 0x68); // Possibly operator delete or custom dealloc
    }
}