// FUNC_NAME: DonControlManager::updateCooldown
// Function address: 0x008c3bc0
// Called when a cooldown timer expires. Iterates over entity list to clear action states.
void __thiscall DonControlManager::updateCooldown(int this, int entityResult) {
    int *timerPtr;
    char validFlag;
    int *nodePtr;
    int player;

    // Clear bit 31 of the entity's state at offset 0x1b94 (maybe "inCooldown" flag)
    *(uint *)(entityResult + 0x1b94) &= 0x7fffffff;

    // Decrement the manager's timer tick count at +0xec
    timerPtr = (int *)(this + 0xec);
    *timerPtr = *timerPtr - 1;
    if (*timerPtr == 0) {
        // Timer fully expired → call end scene/action start
        FUN_008c1730(1, 0);
        return;
    }

    // When timer reaches 1 (just before expiration), process the entity list
    if (*(int *)(this + 0xec) == 1) {
        // Get the linked list of entities from +0x88
        nodePtr = (int *)FUN_0043c2c0(*(int *)(this + 0x88));
        // Iterate over the list (offset 0 = data, offset 4 = next)
        for (nodePtr = (int *)*nodePtr; nodePtr != 0; nodePtr = (int *)nodePtr[1]) {
            entityResult = 0;
            // Call virtual function at vtable offset 0x10 (e.g., "resolveEntityByHash")
            validFlag = (*(code **)(*(int *)*nodePtr + 0x10))(0x55859efa, &entityResult);
            if (((validFlag != '\0') && (entityResult != 0)) &&
                (*(int *)(entityResult + 0x1b94) < 0) &&
                ((player = FUN_0043b870(DAT_01130950), player != 0) &&
                 (validFlag = FUN_008a4380(), validFlag == '\0'))) {
                // Clear bit 8 (0x100) in player's action flags at +0x4c (e.g., "cooldownFinished")
                *(uint *)(player + 0x4c) &= 0xfffffeff;
            }
        }
    }
}