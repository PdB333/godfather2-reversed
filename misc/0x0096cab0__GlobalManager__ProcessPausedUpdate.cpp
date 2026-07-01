// FUNC_NAME: GlobalManager::ProcessPausedUpdate
void __fastcall GlobalManager::ProcessPausedUpdate(int* param_1) {
    GlobalManager* globalMgr = (GlobalManager*)DAT_01129828; // Singleton instance of GlobalManager
    FUN_008f1e70(0x40); // Likely a memory/lock call (size 0x40)
    bool isActive = globalMgr->IsActive(); // Virtual at +0x24, returns bool
    // Check if active and not paused (bit 7 clear in flags)
    if (isActive && !(globalMgr->flags & kPausedFlag)) {
        // Call virtual method on the parameter object (e.g., ControllerState) at +0xC
        ((VirtualFunc*)param_1)->Method12(); // Probably UpdateInput or similar
        FUN_00911b00(); // Update related subsystem
        globalMgr->ScheduleCallback(LAB_0096aa20, 0); // Virtual at +0x18, e.g., postUpdate
        return;
    }
    // If not active but still not paused, handle alternate path
    if (!(globalMgr->flags & kPausedFlag)) {
        if (globalMgr->flags & kFlagBit10) {
            globalMgr->flags &= ~kFlagBit10; // Clear bit 10
        }
        globalMgr->ScheduleDeferredCallback(LAB_0096aa20, 0, 0); // Virtual at +0x14
    }
}