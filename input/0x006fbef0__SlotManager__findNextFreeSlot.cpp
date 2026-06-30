// FUNC_NAME: SlotManager::findNextFreeSlot
// Function at 0x006fbef0
// Searches for a slot (among 3, each 0x58 bytes) with state 0 or 6 starting from lastIndex+1.
// Returns slot index in *outSlotIndex and boolean success.
// Struct fields:
//   +0x20c: int lastIndex (last used slot index)
//   +0x78: array[3] of Slot, each 0x58 bytes
//   Slot+0x00: int state (0=free, 6=done/ready)
//   Slot+0x20: int useCount

char __thiscall SlotManager::findNextFreeSlot(void* thisPtr, int* outSlotIndex)
{
    int* slotBase;
    int currentIndex;
    int slotState;
    char found = '\0';
    int slotIndex = -1;
    int iteration = 1;

    do {
        if (found != '\0') break;
        // Round-robin: start from lastIndex+1
        currentIndex = (*(int*)((char*)thisPtr + 0x20c) + iteration) % 3;
        // Get slot base pointer
        slotBase = (int*)((char*)thisPtr + currentIndex * 0x58 + 0x78);
        slotState = *slotBase; // first DWORD of slot is state
        if (slotState == 0 || slotState == 6) {
            *(int*)((char*)thisPtr + 0x20c) = currentIndex;
            found = '\x01';
            slotIndex = currentIndex;
        }
        iteration++;
    } while (iteration < 4);

    if (slotIndex != -1) {
        // Increment useCount at slot offset +0x20 (0x98 - 0x78 = 0x20)
        int* useCountPtr = (int*)((char*)thisPtr + slotIndex * 0x58 + 0x98);
        *useCountPtr = *useCountPtr + 1;
        *outSlotIndex = slotIndex;
        return found;
    }
    *outSlotIndex = -1;
    return found;
}