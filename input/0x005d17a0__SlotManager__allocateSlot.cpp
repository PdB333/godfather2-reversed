// FUNC_NAME: SlotManager::allocateSlot
int* SlotManager::allocateSlot()
{
    int slotIndex = 0;
    int* slotPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 4); // +0x04: start of slot array

    do {
        // Check if slot is free (status at offset 0x30 == 0)
        if (slotPtr[0xC] == 0) {
            // Mark slot as used (status = 2)
            slotPtr[0xC] = 2;
            // Store slot index in first field (offset 0x00)
            *slotPtr = slotIndex;
            return slotPtr;
        }
        slotIndex++;
        slotPtr += 0x35; // Advance to next slot (0x35 ints = 0xD4 bytes)
    } while (slotIndex < 0xC0); // 192 slots total

    return nullptr; // No free slot found
}