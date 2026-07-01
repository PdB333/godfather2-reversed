// Xbox PDB: EARS_Modules_HudTimerManager_HudTimerManager
// FUNC_NAME: HUDTimerCountdownManager::HUDTimerCountdownManager
HUDTimerCountdownManager* __thiscall HUDTimerCountdownManager::HUDTimerCountdownManager(HUDTimerCountdownManager* this) {
    // Store global singleton pointer
    g_pHUDTimerCountdownManager = this;

    // Set vtable pointers (base class first, then derived?)
    this->vtable1 = &PTR_FUN_00e2f19c;   // initial base vtable
    this->someFlag = 1;                  // +0x08: maybe enabled flag
    this->someCounter = 0;               // +0x0C: countdown active? 
    this->vtable0 = &PTR_FUN_00d83744;   // +0x00: override vtable (multiple inheritance or dynamic)
    this->vtable1 = &PTR_LAB_00d83734;   // +0x04: final vtable (replaces base)
    this->field_0x10 = 0;                // bytes at +0x10 (4 bytes?) but only first byte set
    this->field_0x11 = 0;                // byte at +0x11
    this->field_0x14 = 0;                // +0x14 (4 bytes)
    this->field_0x18 = 0;                // +0x18
    this->field_0x1C = 0;                // +0x1C
    this->field_0x20 = 0;                // +0x20

    // Register message names with the game message system
    GameMessageSystem::registerMessage(&g_iMsgHUDTimerCountdownStart, "iMsgHUDTimerCountdownStart");
    GameMessageSystem::registerMessage(&g_iMsgHUDTimerCountdownEnd,   "iMsgHUDTimerCountdownEnd");

    return this;
}