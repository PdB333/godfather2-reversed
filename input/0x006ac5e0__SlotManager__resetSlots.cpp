// FUNC_NAME: SlotManager::resetSlots
void __fastcall SlotManager::resetSlots(int thisPtr)
{
    // Check if the reset flag (bit 0 at +0x3d4) is set
    if ((*(byte *)(thisPtr + 0x3d4) & 1) != 0) {
        // Iterate over 20 slots (0x14 = 20)
        // Each slot is 12 bytes (0xc) and starts at thisPtr + 0x2c
        // piVar2 points to the third int (pointer) of each slot
        int *slotPtr = (int *)(thisPtr + 0x34); // points to pointer field of first slot
        for (int i = 0; i < 20; i++) {
            // Check if slot is active (bit 1 of flags at offset -8 from slotPtr) and pointer is null
            if ((((uint)slotPtr[-2] >> 1 & 1) != 0) && (*slotPtr == 0)) {
                // Call cleanup function for this slot
                FUN_006abee0(); // likely releases resources
            }
            slotPtr += 3; // advance to next slot (3 ints = 12 bytes)
        }
        // Reset counters and flags
        *(int *)(thisPtr + 0x3d0) = 20;   // reset slot count to 20
        *(uint *)(thisPtr + 0x3d4) &= 0xfffffffe; // clear bit 0 (reset flag)
        *(int *)(thisPtr + 0x3dc) = 0;    // clear some counter
        *(int *)(thisPtr + 0x3e4) = 0;    // clear another counter
    }
}