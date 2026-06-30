// FUNC_NAME: unknown::checkSlotAndProcess
// Function address: 0x0053de70
// Role: Checks if a specific slot (identified by global index g_activeSlotIndex) in an array is active (non-zero first byte) and calls a handler if so.
// Assumes g_slotArray is an array of 0x1B-byte structures; first byte is an active flag.

// Forward declaration of the called handler (address 0x006063b0)
void processActiveSlot();

// Global data (from Ghidra symbols)
// DAT_0121bf30 - stores an index into the slot array
extern int g_activeSlotIndex; 

// DAT_01198ec4 - base of slot array. Each slot is 0x1B bytes.
// We define a struct representing the start of each slot; only the first byte is used here.
struct SlotHeader {
    char active; // +0x00: non-zero if slot is occupied/active
    // padding/rest of slot (0x1A bytes)
};

extern SlotHeader g_slotArray[]; // address of DAT_01198ec4 reinterpreted

void checkSlotAndProcess()
{
    // Access the slot at the given index
    SlotHeader& slot = g_slotArray[g_activeSlotIndex];
    if (slot.active != 0) {
        processActiveSlot();
    }
}