// FUNC_NAME: PlayerSlotManager::removePlayerFromSlot
int __thiscall PlayerSlotManager::removePlayerFromSlot(int this, int playerId)
{
    int *slotArray = *(int **)(this + 0x603c); // pointer to array of slot structures, each 0x74 bytes (29 ints)
    int result = 0;
    int slotIndex = 0;
    int *currentSlot = slotArray;
    int *endSlot = slotArray + 0x3a00; // 14848 ints ahead → 512 slots (14848 / 29)
    if (slotArray != (int *)0x0) {
        while (currentSlot < endSlot) {
            // slot layout: [0] = pointer to some object (maybe network object)
            //                [1] = pointer to player/connection object (with ID at offset +4)
            if ((int *)*currentSlot != (int *)0x0) {
                if (currentSlot[1] != 0) {
                    // check if the player ID at connection+4 matches the target
                    if (*(int *)(currentSlot[1] + 4) != playerId) {
                        goto nextSlot;
                    }
                    FUN_005dbc10(slotIndex, *(int *)*currentSlot); // remove/cleanup slot object
                }
                FUN_005e63e0(slotIndex); // finalize slot removal
            }
nextSlot:
            slotIndex++;
            currentSlot += 0x1d; // advance to next slot (29 ints per slot)
        }
        result = 1;
    }
    return result;
}