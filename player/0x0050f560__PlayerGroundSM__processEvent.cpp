// FUNC_NAME: PlayerGroundSM::processEvent
void __thiscall PlayerGroundSM::processEvent(PlayerGroundSM* this, uint param_2) {
    // +0x58: pointer to some state/component (likely character state machine)
    int statePtr = *(int*)((int)this + 0x58);
    
    // +0x10: pointer to input/controller manager or similar
    // +0x104: flag byte, bit 0 checked
    if (statePtr != 0 && (*(byte*)(*(int*)((int)this + 0x10) + 0x104) & 1) == 0) {
        // Access thread-local singleton (FS:[0x2C] -> some pointer, +8 -> manager, +0x80 + index*? 
        // This appears to be a per-thread game context or frame manager
        uint* threadLocalPtr = *(uint**)(*(uint**)(__readfsdword(0x2C) + 8) + 0x80 + *(int*)((int)this + 8));
        uint64 val1 = *(uint64*)threadLocalPtr;                 // read 8 bytes
        uint val2 = *(uint*)(threadLocalPtr + 1);               // next 4 bytes
        uint val3 = *(uint*)((int)this + 0x44);                 // some value from this

        // Modify flags on the state object at +0x94 (clear bit 3)
        *(uint*)(statePtr + 0x94) &= 0xFFFFFFF7;

        // Write 8 bytes at +0x80 (low 8 bytes of the TLS data)
        *(uint64*)(statePtr + 0x80) = val1;
        // Write 8 bytes at +0x88 (combination of val2 and val3)
        *(uint64*)(statePtr + 0x88) = ((uint64)val3 << 32) | val2;

        // Call some reset/clear function on the state object
        FUN_0044f770(statePtr, 0);
    }

    // +0x70: state byte (0 = idle, 3 = running, 5 = climbing, etc.)
    byte state = *(byte*)((int)this + 0x70);
    if (state != 0 && state != 3 && state != 5) {
        // If state is not 0, 3, or 5, handle via immediate path
        FUN_00511f00(param_2);
        return;
    }
    // Otherwise, use standard queued/dispatched path
    FUN_00512240(this, param_2);
}