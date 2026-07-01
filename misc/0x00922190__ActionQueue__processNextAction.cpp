// FUNC_NAME: ActionQueue::processNextAction
void __thiscall ActionQueue::processNextAction(int this) {
    int* entryBase = *(int**)(this + 0x5C);      // +0x5C: pointer to array of 8-byte action entries
    uint currentIndex = *(uint*)(this + 0x74);    // +0x74: current index into the action array
    int actionType = *(int*)(entryBase + currentIndex * 2); // each entry is 8 bytes, first int is type

    // Skip null or "hidden" action types (0x48 = 72, likely a special enum value)
    if (actionType == 0 || actionType == 0x48) {
        return;
    }

    // Get a new action object from some factory
    void* actionObj = getNewActionObject(); // FUN_00950b00
    if (actionObj == nullptr) {
        return;
    }

    // Initialize the action object with a special value (-1)
    initializeActionObject(actionObj, -1); // FUN_008e6380

    // Store the current action limit (from +0x60) as the "current"
    *(uint*)(this + 0x78) = *(int*)(this + 0x60); // +0x78: current action reference

    // Apply action effects or trigger a callback
    applyActionEffects(); // FUN_00921320

    // Clear the active processing flag
    *(bool*)(this + 0xA1) = false; // +0xA1: boolean flag for action in progress

    // If we've reached or exceeded the limit, wrap the index back to 0
    uint limit = *(int*)(this + 0x60); // +0x60: maximum allowed index (or count)
    if (limit <= currentIndex) {
        *(uint*)(this + 0x74) = 0; // +0x74: wrap index
    }

    // Finalize or signal completion
    finalizeAction(0); // FUN_00921de0
}