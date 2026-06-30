// FUNC_NAME: SlotManager::releaseSlotByIndex
void __thiscall SlotManager::releaseSlotByIndex(SlotManager* thisPtr, int* sourceObject)
{
    // sourceObject + 0x184 stores the slot index for this object
    int slotIndex = *(int*)((char*)sourceObject + 0x184);

    // Array of 8-byte slots starts at thisPtr + 0x1ac; each slot holds a pointer
    int** slotPtr = (int**)((char*)thisPtr + 0x1ac + slotIndex * 8);

    if (*slotPtr != 0) {
        // Release the resource at slotPtr
        FUN_004daf90(*slotPtr); // Equivalent to operator delete or custom free
        *slotPtr = 0;
    }
}