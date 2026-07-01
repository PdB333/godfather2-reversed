// FUNC_NAME: PlayerActionableTargetSM::resetTargeting
void __thiscall PlayerActionableTargetSM::resetTargeting(PlayerActionableTargetSM* thisPtr) {
    int* globalPtr = (int*)0x01129a74; // Global singleton pointer (e.g., InputDeviceManager or GameManager)
    if (*(char*)(thisPtr + 0x2AD) != '\0') { // Check if targeting is active (byte flag at +0x2AD)
        *(int*)(thisPtr + 0x2B4) = 0; // Clear targeting state integer at +0x2B4
        FUN_00926890(0, 0, 0, 0, 0); // Clear input or state (likely sets all parameters to zero)
        *(char*)(*globalPtr + 0x3A3) = 1; // Set global flag at +0x3A3 to 1 (e.g., enable input)
        *(char*)(thisPtr + 0x2AD) = 0; // Clear the active flag
    }
}