// FUN_00519ac0: EARSObject::EARSObject
undefined4 __thiscall EARSObject::EARSObject(undefined4 this, byte flags)
{
    // Call the base class constructor (likely sets up vtable and basic fields)
    EARSObject::baseConstructor(); // FUN_00519af0

    // If the dynamic allocation flag (bit 0) is set, register with the memory manager
    if (flags & 1) {
        // Retrieve the global memory manager instance
        MemoryManager* mgr = MemoryManager::getInstance(); // FUN_009c8f80
        // Call the registration virtual function at vtable+0x4
        // The second parameter (0) might indicate operation type or nesting level
        mgr->registerObject(this, 0); // (**(code **)(*mgr->vtable + 4))(this, 0)
    }

    return this;
}