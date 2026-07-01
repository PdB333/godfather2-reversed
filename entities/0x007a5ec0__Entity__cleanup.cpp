// FUNC_NAME: Entity::cleanup
void __fastcall Entity::cleanup(int *this) {
    int state;
    int flags;
    int *subObjectPtr;
    int iVar2;

    // Check if the entity's state is valid (not 0 or 0x48) and the cleanup flag (bit 10) is set
    state = this[0x1d3]; // +0x74C: state ID or type
    if ((state != 0) && (state != 0x48)) {
        flags = this[0x238]; // +0x8E0: flags (bit 10 = pending cleanup)
        if ((flags >> 10 & 1) != 0) {
            // Call a virtual method at index 0x98 (0x260/4) in the vtable
            (*(void (__thiscall **)(int *))(*(int *)this + 0x260))(this);
        }
    }

    // Handle a sub-object pointer at +0x30C0
    subObjectPtr = this + 0xc30; // actually pointer to pointer
    if ((*subObjectPtr != 0) && (*subObjectPtr != 0x48)) {
        // Compute adjusted integer: subtracting 0x48 (72) which is a sentinel/reserved value
        // Then add 0x3c to get the actual allocation offset
        iVar2 = *subObjectPtr - 0x48;
        if (*subObjectPtr == 0) {
            iVar2 = 0;
        }
        // Free memory at the adjusted address
        FUN_004088c0(iVar2 + 0x3c);
        // Destruct the sub-object
        if (*subObjectPtr != 0) {
            FUN_004daf90(subObjectPtr);
            *subObjectPtr = 0; // Clear pointer
        }
    }

    // Final cleanup call
    FUN_004719e0();
    return;
}