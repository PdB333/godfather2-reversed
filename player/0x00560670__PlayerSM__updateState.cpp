// FUNC_NAME: PlayerSM::updateState
void __thiscall PlayerSM::updateState(int arg) {
    // +0x10c: state enum (0,1,2...)
    // +0x110: flags bitmask
    // +0xd4: pointer to some object (e.g., target or data)
    
    if (*(int*)(this + 0x10c) == 2) {
        // In state 2: check if we should exit
        bool bit2Set = (*(uint*)(this + 0x110) >> 2) & 1;
        bool nullPointer = (*(int*)(this + 0xd4) == 0);
        bool bit3Set = (*(uint*)(this + 0x110) >> 3) & 1;
        
        if (bit2Set || nullPointer || bit3Set) {
            FUN_005606c0(arg);
            FUN_00560b30();
            // Clear bit 2 of flags (mask 0xfffffffb = ~(1<<2))
            *(uint*)(this + 0x110) &= 0xfffffffb;
            return;
        }
    }
    else if (*(int*)(this + 0x10c) == 1) {
        // State 1: just call helper
        FUN_005606c0(arg);
    }
    // No action for other states
}