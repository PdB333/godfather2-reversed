//FUNC_NAME: checkActivePlayerSlot
// Function address: 0x0053bb60
// Checks if the current player slot (indexed by global gCurrentSlotIndex) is active,
// and if so, calls a processing function (likely for updating that slot).
// Slot structure size: 0x3c (60 bytes), active flag at offset 0.

extern int gCurrentSlotIndex; // DAT_01125389
extern uint8_t gSlotArrayBase[]; // DAT_011254c0

void processActiveSlot(void); // FUN_006063b0

void checkActivePlayerSlot(void)
{
    // Each slot is 0x3c bytes; check the first int (active flag)
    if (*(int*)(gSlotArrayBase + gCurrentSlotIndex * 0x3c) != 0)
    {
        processActiveSlot();
    }
}