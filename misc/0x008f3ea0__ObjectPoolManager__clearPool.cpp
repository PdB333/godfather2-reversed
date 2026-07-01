// FUNC_NAME: ObjectPoolManager::clearPool
// Function at 0x008f3ea0: Clears a fixed-size pool of objects (6 slots, each 0x558 bytes).
// The pool is stored inline at the start of the object, with a count field at +0x2010.
// Processes all slots except the last one, then resets the count to 0.
void __thiscall ObjectPoolManager::clearPool(void)
{
    uint slotIndex;
    int slotPtr;

    // If count is 0 or 1, just reset and return (no processing needed)
    if (this->m_slotCount == 0) {
        this->m_slotCount = 0;
        return;
    }
    if (this->m_slotCount == 1) {
        this->m_slotCount = 0;
        return;
    }

    slotIndex = 0;
    slotPtr = (int)this; // Start of inline array (offset 0)

    // Loop through slots 0 to count-2 (skip the last slot)
    while (slotIndex < this->m_slotCount - 1) {
        // Process the slot (global function? Or missing argument?)
        FUN_008f2020(); // Possibly processSlot() – no arguments shown
        if (slotPtr != 0) {
            FUN_008f2530(); // Possibly releaseSlot() – no arguments shown
        }
        slotIndex++;
        slotPtr += 0x558; // Move to next slot (size 0x558)
    }

    // Reset count to 0 after processing
    this->m_slotCount = 0;
}