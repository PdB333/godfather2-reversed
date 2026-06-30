// FUNC_NAME: GameEngine::initializeSystems
// Function address: 0x00463df0
// Role: Constructor/initializer for the main game engine object.
// Sets vtable, calls virtual method on subsystem, advances state, resets global flag, and calls sub-initializer.

void __thiscall GameEngine::initializeSystems(void)
{
    // Set vtable for this object (offset 0x00)
    this->vtable = (void**)&PTR_FUN_00e31e58; // vtable pointer

    // Set initial state pointer (offset 0x08)
    this->m_currentState = &PTR_LAB_00e31e64;

    // Call virtual function at offset 0x0C from the vtable of the inner object at offset 0x0C
    (*(void (__thiscall **)(void))(*(int*)this->m_innerObject + 0x0C))();

    // Advance state pointer (offset 0x08)
    this->m_currentState = &PTR_LAB_00e31e68;

    // Reset global initialization flag (address 0x01223460)
    g_bSystemInitialized = 0;

    // Call subsystem initialization function (address 0x0049c640)
    subInit_0049c640();

    return;
}