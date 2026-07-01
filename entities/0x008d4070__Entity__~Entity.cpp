// FUNC_NAME: Entity::~Entity

void __thiscall Entity::~Entity(Entity *this)
{
    // Restore base class vtable pointers for correct destructor chain
    this->vtable = &PTR_FUN_00d7d5b4;                     // +0x00
    *(void **)((char *)this + 0x4C) = &PTR_LAB_00d7d5a4; // +0x4C

    // If global registration flag set, release the global resource
    if (*(char *)((char *)this + 0x81) != 0) {
        FUN_004086d0(&DAT_0112f9dc);   // Unregister from global list
        *(char *)((char *)this + 0x81) = 0;
    }

    // Restore to actual base class vtables (for full destruction chain)
    this->vtable = &PTR_FUN_00d7d588;                     // +0x00
    *(void **)((char *)this + 0x4C) = &PTR_LAB_00d7d578; // +0x4C

    // Destroy two sub-objects at known offsets
    FUN_00408310((int *)((char *)this + 0x58));  // offset 0x58
    FUN_00408310((int *)((char *)this + 0x68));  // offset 0x68

    // Global engine cleanup
    FUN_004083d0();
    FUN_008d2680();
}