// FUNC_NAME: DonControlManager::update
// Address: 0x0097a1f0
// Role: Updates don control state machine, handles transition to cutscene/event state

int __thiscall DonControlManager::update(int thisPtr) {
    // Check if some counter at +0x138 is less than 1 and a global flag bit 10 is clear
    if (*(int*)(thisPtr + 0x138) < 1 && ((*(uint*)(DAT_0112af70 + 0x60) >> 10) & 1) == 0) {
        // Set state to 5 (e.g., STATE_CUTSCENE_TRIGGER)
        *(int*)(thisPtr + 0x14c) = 5;

        // Check if two pointers at +0x13c and +0x140 are non-null and equal (e.g., same target)
        if (*(int*)(thisPtr + 0x13c) != 0 && *(int*)(thisPtr + 0x13c) == *(int*)(thisPtr + 0x140)) {
            // Sequence of function calls to set up cutscene/event
            FUN_00976e00();          // likely startCutscene
            FUN_00976d00(1);         // setCutsceneFlag
            FUN_0094b210(1);         // enableInputBlock
            FUN_00785db0(1);         // pauseGame
            int uVar2 = FUN_00956910(); // getSomeId
            FUN_00979700(uVar2);     // setCutsceneId
            FUN_00978e60(1);         // enableCameraControl
            FUN_00978f70(1);         // enablePlayerControl
            short uVar1 = FUN_009568f0(); // getSomeShort
            FUN_00979b10(uVar1);     // setCutsceneDuration
            FUN_00979900(*(char*)(thisPtr + 0xb4)); // setCutsceneCharacter
            FUN_00976990();          // finalizeCutsceneSetup
            // Set flag bit 6 at +0x60 (e.g., FLAG_CUTSCENE_ACTIVE)
            *(uint*)(thisPtr + 0x60) |= 0x40;
        }

        // Call update on three managers via vtable offset 0x28
        (**(code**)(*(int*)DAT_0113005c + 0x28))(); // e.g., CameraManager::update
        (**(code**)(*(int*)DAT_01129a74 + 0x28))(); // e.g., InputManager::update
        (**(code**)(*(int*)DAT_01130020 + 0x28))(); // e.g., UIManager::update

        // Transition to state 3 if not already (e.g., STATE_CUTSCENE_ACTIVE)
        if (*(int*)(thisPtr + 0x158) != 3) {
            *(int*)(thisPtr + 0x158) = 3;
            // Set a timer/callback with data at +0x14, target function LAB_00978e20, delay 0
            FUN_005c0d50(thisPtr + 0x14, &LAB_00978e20, 0);
        }
    }
    return 1;
}