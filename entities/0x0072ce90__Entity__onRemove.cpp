// FUNC_NAME: Entity::onRemove
// Address: 0x0072ce90
// This function is a __thiscall member of a class (likely Entity or derived).
// It performs cleanup steps: calls a virtual finalizer, global cleanup, sets active state to false,
// and conditionally destroys a child component.

void __thiscall Entity::onRemove()
{
    // Call virtual function at vtable offset 0x308 (index 0xC2) – finalize/preRemove
    (*(void (__thiscall **)(void*))(*reinterpret_cast<int*>(this) + 0x308))(this);

    // Global cleanup function (e.g., MemoryManager::release or scene manager)
    FUN_00625030();

    // Call virtual function at vtable offset 0x234 (index 0x8D) – setActive(false, true)
    (*(void (__thiscall **)(void*, int, int))(*reinterpret_cast<int*>(this) + 0x234))(this, 0, 1);

    // Check if entity is marked for deletion (returned from some global state)
    if (FUN_007f47a0() != 0)
    {
        // Destroy or clean up the component at offset 0x3C (60 bytes) from this
        // This may be a pointer to a child object (e.g., component or state machine)
        FUN_004088c0(reinterpret_cast<int*>(this) + 0xF);  // +0xF * 4 = offset 0x3C
    }
}