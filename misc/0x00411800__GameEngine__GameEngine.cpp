// FUNC_NAME: GameEngine::GameEngine
void __thiscall GameEngine::GameEngine(GameEngine* this)
{
    // Set vtable pointer
    this->vtable = (void**)&PTR_FUN_00e2f4c8; // +0x00
    // Initialize subclass pointer (offset +0x0C)
    this->field_0C = (void*)&PTR_LAB_00e2f4d8; // +0x0C
    // Initialize two global subsystems
    FUN_00408310(&DAT_01206a20); // First subsystem init
    FUN_00408310(&DAT_01206a28); // Second subsystem init
    // Update subclass pointer
    this->field_0C = (void*)&PTR_LAB_00e2f4dc; // +0x0C (updated)
    // Clear global initialization flag
    g_bInitialized = 0; // DAT_012233b8 = 0
    // Final initialization step
    FUN_004083d0();
    return;
}