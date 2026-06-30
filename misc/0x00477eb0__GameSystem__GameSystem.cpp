// FUNC_NAME: GameSystem::GameSystem

// Constructor for a core game system (EARS engine). Sets up vtable pointers for multiple base classes,
// then initializes a sub-component and registers globally.
void __fastcall GameSystem::GameSystem(GameSystem* this)
{
    // Set primary vtable (GameSystem vtable)
    this->vfptr = (void**)&PTR_FUN_00e32f6c;
    // Set secondary vtable at offset 0x3C (likely for interface like IUpdateable)
    *(void**)((uint8_t*)this + 0x3C) = (void*)&PTR_LAB_00e32f88;
    // Set tertiary vtable at offset 0x48 (likely for interface like IRenderable)
    *(void**)((uint8_t*)this + 0x48) = (void*)&PTR_LAB_00e32f98;
    // Register this object in a global system list (via a singleton at DAT_0120e93c)
    FUN_004086d0(&DAT_0120e93c);
    // Construct a sub-object at offset 0x50 (e.g., a list or message queue)
    FUN_00408310(this + 0x14);
    // Perform global initialization (e.g., memory manager, input system)
    FUN_0046c640();
}