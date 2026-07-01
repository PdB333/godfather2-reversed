// FUNC_NAME: MissionObjective::updateState
void __thiscall MissionObjective::updateState(void* this_ptr, void* missionObj) {
    char charVar1;
    undefined4 retVal;
    int intVar3;
    
    if (missionObj != nullptr) {
        // Profile scope start
        FUN_00471610();
        // Call virtual function on missionObj (likely onEvent)
        (*(code**)(*(int*)missionObj + 0x1c))();
        FUN_004706f0();
        // Set flag bit 3 at offset 0x1F5C (0x7D7 * 4 = 0x1F5C)
        *(int*)((int)missionObj + 0x1F5C) = *(int*)((int)missionObj + 0x1F5C) | 8;
        FUN_0083f190();
        // Assign a static string/constant to offset 0x158 (0x56 * 4 = 0x158)
        *(int*)((int)missionObj + 0x158) = (int)&DAT_008755c0;
        // Check if missionObj is non-null and bit 21 of this+0xC88 is clear
        if (((char)missionObj != '\0') && (((*(uint*)((int)this_ptr + 0xC88) >> 0x15) & 1) == 0)) {
            intVar3 = 0;
            // Check bit 11 of this+0xC88
            if (((*(uint*)((int)this_ptr + 0xC88) >> 0xb) & 1) != 0) {
                intVar3 = *(int*)((int)this_ptr + 0xB90); // this[0x2E4] (0xB90)
            }
            // Check bit 6 of this+0xA18
            if (((*(uint*)((int)this_ptr + 0xA18) >> 6) & 1) != 0) {
                intVar3 = *(int*)((int)this_ptr + 0xB90);
            }
            if (intVar3 != 0) {
                // Call virtual function on missionObj (index 0x1C4 -> method 113)
                (*(code**)(*(int*)missionObj + 0x1C4))(intVar3);
                if (intVar3 != 0x637B907) {
                    // Clear bit 9 at offset 0x1F54 (0x7D5 * 4 = 0x1F54)
                    *(int*)((int)missionObj + 0x1F54) = *(int*)((int)missionObj + 0x1F54) & 0xFFFFFDFF;
                }
            }
        }
        charVar1 = FUN_008759d0(); // Likely checks if mission is active
        if (charVar1 == '\0') {
            FUN_004088c0(); // Handle mission end?
            if ((*(byte*)((int)this_ptr + 0xC8A) & 1) != 0) {
                // Call virtual function on this (index 0x2AC -> method 171)
                (*(code**)(*(int*)this_ptr + 0x2AC))();
            }
        } else {
            // Call virtual function on missionObj (index 0x1AC -> method 107)
            (*(code**)(*(int*)missionObj + 0x1AC))();
            FUN_007F63E0(4); // Set some flag
            // Call virtual function on this (index 0x1F8 -> method 126) with missionObj and stack param
            (*(code**)(*(int*)this_ptr + 0x1F8))(missionObj, &stack0xFFFFFFF0);
            // Check mission type (via this pointer comparison, likely enum)
            if ((((this_ptr == (void*)0x6) ||
                  ((this_ptr != (void*)&DAT_00000008 && ((this_ptr == (void*)0xA || (this_ptr == (void*)0xC)))))
                 ) && (this_ptr != (void*)&DAT_00000008)) &&
                (((this_ptr != (void*)0x9 && (this_ptr != (void*)0xC)) && (this_ptr != (void*)0xD)))) {
                // Call virtual function on this (index 0x20C -> method 131)
                (*(code**)(*(int*)this_ptr + 0x20C))(missionObj);
            }
            retVal = (*(code**)(*(int*)this_ptr + 0x280))(&stack0xFFFFFFE8); // method 160
            intVar3 = FUN_00875AF0(missionObj, retVal); // Get remaining time or something
            *(int*)((int)missionObj + 0x1F10) = intVar3; // offset 0x7C4 * 4 = 0x1F10
            charVar1 = *(char*)((int)this_ptr + 0xC80); // byte at offset 0xC80
            if (charVar1 != '\0') {
                *(char*)((int)this_ptr + 0xC80) = charVar1 - 1; // decrement counter
                FUN_00878310(missionObj); // Apply mission completion
                return;
            }
        }
    }
}