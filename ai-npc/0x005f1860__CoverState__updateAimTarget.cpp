// FUNC_NAME: CoverState::updateAimTarget
void __thiscall CoverState::updateAimTarget(void* thisPtr, void* aimData) {
    // thisPtr = unaff_ESI, aimData = in_EAX (likely a structure with aim parameters)
    // Offsets:
    // +0x00: vtable? (not used)
    // +0x08: pointer to some data/state (e.g., coverNode or action state)
    // +0x68: current state (4 == out of cover? or non-cover state?)
    // +0x6c: flags (bit0 = something)
    // +0x84: base aim target (e.g., base direction)
    // +0x8c: computed aim target (final direction after adjustments)

    if (aimData == NULL || thisPtr == NULL) return;
    int* statePtr = *(int**)((char*)thisPtr + 0x08);
    if (statePtr == NULL) return;
    if (*(int*)((char*)thisPtr + 0x68) == 4) return; // state 4 is inactive? skip

    // Check a byte at statePtr[1] (offset 1 from statePtr)
    if (*(char*)((char*)statePtr + 1) == '\0') {
        // Not aiming? Use base target directly
        *(int*)((char*)thisPtr + 0x8c) = *(int*)((char*)thisPtr + 0x84);
    } else {
        // Aiming: compute aim adjustment via helper
        FUN_005f20c0();
    }

    // Apply aim data adjustment
    unsigned char multiplier = *(unsigned char*)((char*)aimData + 3); // byte multiplier
    *(unsigned short*)((char*)thisPtr + 0x6c) |= 1; // set flag bit0
    *(int*)((char*)thisPtr + 0x8c) += (int)multiplier * 8; // adjust target

    // Trigger updates
    FUN_005e5200(1); // e.g., setDirtyFlag(1)
    FUN_005dbc10();  // e.g., applyAim()
}