// FUNC_NAME: areAllSlotsFreeExceptFirst
// Function address: 0x00666800
// Checks if all entries in an array (starting from index 1) are set to the invalid sentinel value 0xFFFFFFF (-1).
// Returns true only if the count >= 2 and every slot from index 1 to count-1 holds the sentinel.
// This indicates that only the first slot (index 0) is populated and the rest are free.

bool areAllSlotsFreeExceptFirst(void)
{
    int slotCount = *(int*)this;                    // Field at offset 0x00: number of slots
    if (slotCount < 2)
    {
        return false;
    }

    int* slotArray = *(int**)((char*)this + 0x0C); // Field at offset 0x0C: pointer to array of slot values
    for (int i = 1; i < slotCount; i++)
    {
        if (slotArray[i] != -1)                     // 0xFFFFFFF == -1 (invalid/uninitialized)
        {
            return false;
        }
    }
    return true;
}