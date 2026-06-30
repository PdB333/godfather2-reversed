// FUNC_NAME: PlayerSM::handleActionSlot
uint __thiscall PlayerSM::handleActionSlot(PlayerSM *this, uint *outSlotValue, void *pData, uint actionType, uint extraParam) {
    uint result; // uVar1 (masked with 0xffffff00)
    uint slotValue;

    result = 0; // initialize with masked in_EAX, but seems unused in path
    *outSlotValue = 0;

    // Check if the action system is active (offset 0x1744 = flag)
    if (*(bool *)((int)this + 0x1744) && pData != nullptr) {
        uint slotIndex = getActionSlotIndex(this, actionType); // FUN_005e26a0

        if (slotIndex < 5) {
            // Access the slot array element (size 0x4a4) at the given index
            // param_1 becomes a pointer to the specific slot structure
            SlotStruct *slot = (SlotStruct *)((int)this + slotIndex * 0x4a4);

            // Check if some condition is met (FUN_005e8670)
            if (isConditionMet()) { // likely returns bool
                slotValue = getSlotValue(); // FUN_005e2680
                *outSlotValue = slotValue;
                slot->slotField490 = slotValue; // offset 0x490 within slot structure

                // Release previous data (FUN_004d3d90)
                releaseData(pData); // might be a destory or unref

                // Apply the action to the slot (FUN_005e9220)
                // slot + 4 suggests offset 0x4 within the slot struct is used as a base
                result = applyActionToSlot((SlotInternal *)((int)slot + 4), pData, actionType, extraParam);
                return result;
            }
        }
        result = 0; // return 0 (masked with 0xffffff00 is already 0)
    }
    return result;
}

// NOTE: The actual function uses in_EAX to initialize uVar1, but that's an artifact of decompilation.
// The code path only produces a return value from applyActionToSlot or defaults to 0 with high byte cleared.