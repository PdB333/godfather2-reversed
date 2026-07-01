// FUNC_NAME: PlayerSM::enterState_2
void __fastcall PlayerSM::enterState_2(int this)
{
    int *vtable;
    float value;

    // If not already in state 2, set a flag indicating state transition
    if (*(int *)(this + 0xf2c) != 2) {
        *(uint *)(this + 0xf28) |= 0x40000; // +0xf28: stateFlags, bit 18 = stateChangePending
    }
    // Set current state to 2
    *(int *)(this + 0xf2c) = 2; // +0xf2c: currentState
    // Clear bit 19 (0x80000) from stateFlags
    *(uint *)(this + 0xf28) &= 0xfff7ffff; // +0xf28: stateFlags

    // Get the audio manager pointer (likely EARS::AudioDataManager or similar)
    vtable = *(int **)(this + 0x130); // +0x130: audioManager
    if (vtable != (int *)0x0) {
        // Call audio events via vtable function at offset 0x48 (playEvent or similar)
        (**(code **)(*vtable + 0x48))(0xe68ab829, *(uint *)(this + 0xc88) >> 2 & 0xffffff01); // +0xc88: some flags
        (**(code **)(*vtable + 0x48))(0xe143e67d, 1);
        (**(code **)(*vtable + 0x48))(0xbe171efb, 1);
    }

    // Clear bit 20 (0x100000) from stateFlags
    *(uint *)(this + 0xf28) &= 0xffcfffff; // +0xf28: stateFlags

    value = *(float *)(this + 0x1034); // +0x1034: some speed/scale value
    if (_DAT_00d577a0 <= value) { // Global threshold
        if ((~(byte)(*(uint *)(this + 0xc88) >> 2) & 1) != 0) {
            if ((*(uint *)(this + 0xc88) >> 0xb & 1) != 0) goto LAB_0086236e;
            value = value * DAT_00d5eee4; // Scale factor
        }
        FUN_00546940(value); // Apply some effect (likely audio or physics)
    }
LAB_0086236e:
    // If bit 14 (0x4000) was set in flags, clear it and notify something
    if ((*(uint *)(this + 0xc88) & 0xffffbfff) != *(uint *)(this + 0xc88)) {
        (**(code **)(*(int *)(this + 0x58) + 0x28))(0x10); // +0x58: some object, vtable+0x28 = notify
        *(uint *)(this + 0xc88) &= 0xffffbfff; // +0xc88: flags, clear bit 14 (0x4000)
    }
}