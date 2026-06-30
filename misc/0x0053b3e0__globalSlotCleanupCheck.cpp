// FUNC_NAME: globalSlotCleanupCheck

// Based on Ghidra decompilation at 0x0053b3e0.
// Checks if a slot in an array of 0x3c-byte structures is active, and if so calls cleanup.
// Global index DAT_01125389 indexes into an array at base DAT_011254a8.
// Each structure is 0x3c bytes. The first field (offset +0x0) is a 4-byte active flag.

extern int gSlotIndex;             // DAT_01125389
extern uint8_t* gSlotArrayBase;    // DAT_011254a8

void cleanupSlot();                // FUN_006063b0

void globalSlotCleanupCheck(void)
{
    // Check if the first field of the indexed slot is non-zero
    if (*(int*)(gSlotArrayBase + (uint)gSlotIndex * 0x3c) != 0) {
        cleanupSlot();
    }
    return;
}