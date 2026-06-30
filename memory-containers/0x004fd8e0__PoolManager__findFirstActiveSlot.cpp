// FUNC_NAME: PoolManager::findFirstActiveSlot
// This function searches through an array of 0x90-byte slots for the first one with a flag at offset 0x78 having bit 0 set.
// Returns a pointer to the slot (as an integer) or 0 if none found.
// The class containing this function has:
//   +0x34: pointer to the first slot (base address of the array)
//   +0x3c: number of slots (count)

int __fastcall PoolManager::findFirstActiveSlot(int thisPtr)
{
    int index = 0;
    if (*(int *)(thisPtr + 0x3c) > 0) {          // if count > 0
        byte *pFlag = (byte *)(*(int *)(thisPtr + 0x34) + 0x78); // point to flag byte of first slot
        do {
            if ((*pFlag & 1) != 0) {
                // Active slot found, return pointer to slot (base + index * slotSize)
                return index * 0x90 + *(int *)(thisPtr + 0x34);
            }
            index = index + 1;
            pFlag = pFlag + 0x90;               // move to next slot's flag (each slot is 0x90 bytes)
        } while (index < *(int *)(thisPtr + 0x3c));
    }
    return 0;                                    // no active slot found
}