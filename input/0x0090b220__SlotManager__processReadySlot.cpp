// FUNC_NAME: SlotManager::processReadySlot
void __fastcall SlotManager::processReadySlot(void* this) {
    int slotIndex;
    int basePtr;
    uint* slotFlags;
    uint* currentSlot;
    uint currentTime;

    // Assert that the manager state is initialized (value at +0x14 must be 1)
    if (*(int*)((char*)this + 0x14) != 1) {
        FUN_007e7df0(0x34);  // Assertion/log
    }

    slotFlags = (uint*)((char*)this + 0x18);  // Array of 7 slot structures, each 0x24 bytes
    slotIndex = 0;
    currentSlot = slotFlags;

    // First pass: look for a ready slot among the first 4 indices (0-3)
    // A ready slot has (flags & 1) == 1 and (flags & 2) == 0
    while (((*currentSlot & 1) == 0) || ((*currentSlot >> 1) & 1) != 0) {
        slotIndex++;
        currentSlot += 9;  // Move to next slot (stride = 9 * 4 = 36 = 0x24)
        if (slotIndex > 3) {
            return;  // No ready slot found
        }
    }

    // Found a ready slot at index 'slotIndex'
    basePtr = FUN_007351c0();  // Get some manager/ID

    // Retrieve the global singleton from DAT_012233a0+4 and derive a base pointer
    if (**(int**)(DAT_012233a0 + 4) == 0) {
        // No base pointer
        // (original code sets iVar2 = 0)
    }
    else {
        // Subtract offset 0x1f30 to get the owning object
        basePtr = **(int**)(DAT_012233a0 + 4) - 0x1f30;
    }

    // Initialize/configure the slot using the found index and base pointer
    FUN_0090aa60(slotIndex, basePtr, 0, 0);

    // Operate on a container/list at offset 0x10
    FUN_00791e70((char*)this + 0x10);

    // Get current system time or tick count
    currentTime = FUN_00790150();

    // Set timestamp for this slot (the argument iVar1+0x20 is unclear but likely an offset)
    FUN_008bcf90(slotIndex + 0x20, currentTime);

    // Finalize slot processing
    FUN_0093ee00(slotIndex);

    // Second pass: scan all 7 slots (indices 0-6) for any remaining ready slot
    slotIndex = 0;
    currentSlot = slotFlags;
    while (true) {
        if ((*currentSlot & 1) == 0) {
            return;  // Slot not used – stop scanning (might be end of active slots)
        }
        if (((*currentSlot >> 1) & 1) == 0) {
            break;  // Found a ready slot; return successfully (function ends)
        }
        slotIndex++;
        currentSlot += 9;  // Next slot
        if (slotIndex > 6) {
            // No ready slot found in the whole array; log error
            FUN_00894c90(0xfde43bc9);
            return;
        }
    }
    // If we break here, a ready slot was found; function returns implicitly
}