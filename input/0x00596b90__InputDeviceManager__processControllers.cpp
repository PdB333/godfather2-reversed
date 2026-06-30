// FUNC_NAME: InputDeviceManager::processControllers
void InputDeviceManager::processControllers(void* deltaTime) {
    ControllerSlot* slotArray = (ControllerSlot*)0x0119a9d0; // 16 slots, each 0x74 bytes
    int numSlots = 16;
    // Initialize or reset all controller slots
    for (int i = 0; i < numSlots; i++) {
        ControllerSlot::reset(&slotArray[i]); // FUN_0059b560
    }

    g_inputProcessingGuard = 1; // DAT_0120551f

    // Process active controllers if the manager exists and has active count > 0
    if (g_activeControllerCount != 0 && // DAT_01205598
        (*(code**)(*g_inputManagerVtable + 4))() && // some check on manager
        g_activeControllerCount > 0 &&
        g_controllerInsertMode == 0) { // DAT_012055a0 (bool)
        
        int activeIndex = 0;
        ActiveControllerEntry* activeEntries = (ActiveControllerEntry*)0x01221480; // array of 0x50 each
        while (activeIndex < g_activeControllerCount) {
            if (FUN_00597000() != 0) { // some availability check
                int vtable = *g_controllerVtable; // DAT_012055a4
                void* entryData = FUN_00597370(&activeEntries[activeIndex]); // extract data
                (*(code**)(vtable + 0x24))(entryData); // process input event

                g_activeControllerCount--;
                // Move last active entry to current position (remove from list)
                (*(code**)(*g_inputManagerVtable + 0x10))(
                    &activeEntries[activeIndex],
                    &activeEntries[g_activeControllerCount],
                    0x50
                );
                activeIndex--;
                // activeEntries pointer moves back? Actually code does puVar7 = puVar7 - 0x50 and iVar8 decrement
                // The original loop manipulates pointer and index; we simulate by decrementing index
            }
            activeIndex++;
        }
    }

    // Process each controller slot for state changes
    for (int i = 0; i < numSlots; i++) {
        ControllerSlot* slot = &slotArray[i];
        if (slot->flags & 1) { // slot occupied
            if (!(slot->flags & 0x20)) { // not yet processed?
                FUN_00599720(deltaTime); // update controller state
            }
            if ((slot->flags & 8) && // new device plugged?
                (*(code**)(*g_controllerVtable + 0x18))(slot->someData + 8, 0) != 0) { // check connection
                FUN_005994c0(1, 0); // handle device insertion
            }
        }
    }

    // Clear the "processed" flag (bit 5) from all controller slot flags, for four arrays
    uint flagMask = 0xFFFFFFDD; // ~0x22
    for (int arr = 0; arr < 4; arr++) {
        uint* baseFlags = (uint*)((int)&slotArray[0] + arr * 0x740); // 4 arrays spaced 0x740 apart
        for (int i = 0; i < 16; i++) {
            if (baseFlags[i] & 1) {
                if (baseFlags[i] & 0x20) {
                    baseFlags[i] &= flagMask; // clear bit 5
                }
            }
        }
    }

    g_inputProcessingGuard = 0; // DAT_0120551f
}