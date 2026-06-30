// FUNC_NAME: Player::getCurrentAbilityId
// Function at 0x00737790 - Determines the current ability/action ID based on state flags.
// Returns a 32-bit hash constant representing the ability to perform.
uint32_t __thiscall Player::getCurrentAbilityId(int param_2) {
    uint32_t result = 0;
    int globalState;
    
    if (this == nullptr) {
        globalState = 0;
    } else {
        globalState = FUN_0043b870(DAT_0112af58); // Check global manager state
    }
    
    // Check global bit at +0x1f57
    if ((*(uint8_t*)((uintptr_t)this + 0x1f57) & 1) == 0) {
        // If globalState is non-zero and some function returns true, return default
        if (globalState != 0 && FUN_00782ce0() != 0) {
            return 0xf96a7902; // Default ID for disabled state
        }
        
        // Check flags at offset 0x7e6 (bitfield, stored as 32-bit integer)
        uint32_t flags = *(uint32_t*)((uintptr_t)this + 0x7e6);
        
        if ((flags & 0x1) != 0) {
            // Bit 0 set: check another condition
            bool hasSpecial = (FUN_00736300() != 0);
            if (hasSpecial) {
                return 0xcd10ee17; // Special ability ID
            }
            // else returns 0 (default)
            return 0;
        }
        
        // Test successive bits (1..12)
        if ((flags >> 1) & 1) {
            // Bit 1 set - fall through to default at end
        } else if ((flags >> 2) & 1) {
            return 0xbefdcee6;
        } else if ((flags >> 3) & 1) {
            return 0x49685d51;
        } else if ((flags >> 4) & 1) {
            int count = FUN_0077dd80();
            // If count > 2, return 0x12eaa862; else 0
            return (count > 2) ? 0x12eaa862 : 0;
        } else if ((flags >> 5) & 1) {
            return 0x2907c5c6;
        } else if ((flags >> 6) & 1) {
            return 0xae31df90;
        } else if ((flags >> 7) & 1) {
            return 0x21a0614f;
        } else if ((flags >> 8) & 1) {
            return 0xce59158c;
        } else if ((flags >> 9) & 1) {
            int targetVal = *(int*)((uintptr_t)this + 0x84e); // some field at +0x84e (offset 2126)
            int otherVal = param_2 != 0 ? *(int*)(param_2 + 0x1ed4) : 0; // from param_2
            if (targetVal != otherVal) {
                bool extraFlag = FUN_0090b180() != 0;
                if (extraFlag) {
                    return 0xcf0f2d8a;
                }
                // else return 0
                return 0;
            } else {
                // Call virtual function at vtable+0x1bc
                bool vfuncResult = (*(code**)(*(uintptr_t*)this + 0x1bc))(this) != 0;
                return vfuncResult ? 0x69586fe : 0;
            }
        } else if ((flags >> 10) & 1) {
            return 0xfd4c274e;
        } else if ((flags >> 11) & 1) {
            // Bit 11 set - fall through
        } else {
            // Bit 0..11 not set? Check bit 12
            bool bit12Set = ((flags >> 12) & 1) != 0;
            if (!bit12Set) {
                return 0; // Nothing set
            }
            // If bit 12 set, fall through to default
        }
    }
    
    return 0xf96a7902; // Default if any condition matched the fall-through or bit1 set
}