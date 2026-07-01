// FUNC_NAME: OverlayManager::handleInputAction
void __thiscall OverlayManager::handleInputAction(uint this, int *inputIdPtr) {
    int *entityPtr;
    int *componentPtr;
    int inputId;
    int currentOverlayId;

    // Get the entity/object from the overlay's associated ID
    entityPtr = (int *)FUN_004059b0(*(uint *)(this + 0x24)); // +0x24: overlay's entity reference
    inputId = *inputIdPtr;

    // Compare input ID with stored overlay ID
    if (inputId == *(int *)(this + 0x14)) { // +0x14: overlay's own ID
        if ((entityPtr != 0) &&
            ((componentPtr = (int *)FUN_004025a0(entityPtr), componentPtr != 0 && (componentPtr[9]/*+0x24*/) != 3))) {
            // Play confirmation sound or trigger animation (0x16)
            FUN_0040eac0(1);
            // Send event: 0x16, with overlay reference (but skip if this == 0x3c)
            FUN_004035c0(entityPtr, 0x16, (this != 0x3c) ? this : 0);
            return;
        }
    } else {
        // Check if input matches global close/back button IDs
        if ((inputId != DAT_01206780) && (inputId != DAT_01206778) && (inputId != DAT_01206760)) {
            return;
        }
        // Handle close/back action
        FUN_00403720(0x16, (this != 0x3c) ? this : 0);
        FUN_0040eaf0(1);
    }

    // Execute deferred callback if present
    int *callbackPtr = *(int **)(this + 0x1c); // +0x1c: pointer to a callback structure
    if (callbackPtr != 0) {
        callbackPtr[0] = 0; // Clear callback ID?
        callbackPtr[1] = 0; // Clear callback data?
        FUN_00408a00(callbackPtr, 0); // Invoke callback
    }
}