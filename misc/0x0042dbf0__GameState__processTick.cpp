// FUNC_NAME: GameState::processTick
void __thiscall GameState::processTick() {
    uint savedState = *(uint*)((uint)this + 0x39F8); // +0x39F8: processing flag / previous state
    // Get thread-local context (FS:[0x2C] -> pointer to TLS block)
    int* tlsPtr = *(int**)(*(int*)__readfsdword(0x2C) + 0x2C);
    int* obj1 = (int*)*(int*)((uint)tlsPtr + 0x28); // first object to potentially delete
    int* obj2 = (int*)*(int*)((uint)tlsPtr + 0x24); // second object to potentially delete

    // If obj1 exists, clear its slot and schedule deferred deletion
    if (obj1 != nullptr) {
        *(int*)((uint)tlsPtr + 0x28) = 0; // clear slot
        if (*(int*)((uint)tlsPtr + 0x34) == 0) { // +0x34: deletion guard/lock
            int** listPtr = (int**)(*(int*)0x01206880 + 0x14); // +0x14: pointer to append pointer
            *(*listPtr)++ = (int)&PTR_LAB_0110b708; // replace vtable with destructor vtable
            *(*listPtr)++ = (int)obj1;            // append object to deletion queue
        }
    }

    // Check bit 4 of a state flag at +0x3AF8
    uint stateFlag = *(uint*)((uint)this + 0x3AF8); // +0x3AF8: combat/health state flags
    uint healthResult;
    if ((stateFlag >> 4) & 1) {
        healthResult = FUN_0042cd20((int)this + 0x28, (int)this + 0x38, 1); // likely returns player health or distance
    } else {
        healthResult = 0xFFFFFFFF; // sentinel for "not applicable"
    }

    // Set global flag based on health threshold (0x31 = 49)
    DAT_0120537c = (healthResult < 0x31) ? 1 : 0;

    // Call general update routine
    FUN_0041f2a0();

    // Restore the saved processing state
    *(uint*)((uint)this + 0x39F8) = savedState;

    // Schedule deferred deletion of obj2 (similar pattern)
    if (obj2 != nullptr) {
        *(int*)((uint)tlsPtr + 0x24) = 0;
        if (*(int*)((uint)tlsPtr + 0x34) == 0) {
            int** listPtr = (int**)(*(int*)0x01206880 + 0x14);
            *(*listPtr)++ = (int)&PTR_LAB_0110b640;
            *(*listPtr)++ = (int)obj2;
        }
    }

    // If obj1 existed, perform additional cleanup (e.g., delete self?)
    if (obj1 != nullptr) {
        FUN_00423410();
    }
}