// FUNC_NAME: HitMission::updateState
void __fastcall HitMission::updateState(HitMission* this)
{
    int callbackId;

    // If this is null, callbackId = 0; else callbackId = this + 0x10
    callbackId = (this == nullptr) ? 0 : (int)this + 0x10;

    // Register a callback (likely for a timer or event)
    FUN_005c02f0(callbackId, (void*)0x00959010, 1);

    // Debug/logging call
    FUN_009bf0e0();

    // Wait/sleep for 10 units (probably millis)
    FUN_006915c0(10);

    // Get the global game manager singleton
    GodfatherGameManager* gameMgr = (GodfatherGameManager*)DAT_01129a74;

    // If this mission has a cached flag set
    if (*(char*)(this + 0x2ad) != '\0') {
        // Reset cached duration to 0
        *(int*)(this + 0x2b4) = 0;
        // Call reset function with no parameters
        FUN_00926890(0, 0, 0, 0, 0);
        // Set a flag in the game manager: some cached state is now active
        *(char*)(gameMgr + 0x3a3) = 1;
        // Clear the local cached flag
        *(char*)(this + 0x2ad) = 0;
    }
}