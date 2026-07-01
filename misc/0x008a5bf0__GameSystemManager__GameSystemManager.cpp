// FUNC_NAME: GameSystemManager::GameSystemManager
void __fastcall GameSystemManager::GameSystemManager(GameSystemManager* this)
{
    // Set vtable pointer at offset 0x0
    *(void**)this = (void*)&PTR_FUN_00d799e8;
    // Set secondary vtable pointer at offset 0x28 (param_1[10])
    *(void**)((uint8_t*)this + 0x28) = (void*)&PTR_LAB_00d799d8;

    // Initialize various global subsystem data structures
    subsystemInit(&DAT_0112ebf4);   // +0x? - likely a manager or config
    subsystemInit(&DAT_0112ebec);   // +0x?
    subsystemInit(&DAT_0112ebdc);   // +0x?
    subsystemInit(&DAT_0112ebe4);   // +0x?
    subsystemInit(&DAT_0112ec74);   // +0x?
    subsystemInit(&DAT_0112ebd4);   // +0x?
    subsystemInit(&DAT_0112ebc4);   // +0x?
    subsystemInit(&DAT_0112ebcc);   // +0x?
    subsystemInit(&DAT_0112ebb8);   // +0x?

    // Register and reinitialize a specific subsystem
    subsystemRegister(&DAT_01218040);
    subsystemInit(&DAT_01218040);

    // Finalize initialization and start core systems
    finalizeInit();
    startSystems();
}