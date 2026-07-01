// FUNC_NAME: SlotManager::initializeSlots

// Reconstructed from function at 0x008b7ca0
// Class that manages 64 slots of 20 bytes each (5 ints) plus an extra int at offset 0x500

struct SlotEntry {
    int field0;   // +0x00
    int field4;   // +0x04
    int field8;   // +0x08
    int fieldC;   // +0x0C
    int field10;  // +0x10
};

class SlotManager {
public:
    SlotEntry slots[64]; // offset 0x00, size 64*0x14 = 0x500
    int extraInt;        // offset 0x500

    // Initialize all slots to zero and the extra int to zero
    void __fastcall initializeSlots();
};

void __fastcall SlotManager::initializeSlots() {
    // Loop over 64 slots (0x40 iterations)
    for (int i = 0; i < 64; i++) {
        slots[i].field0  = 0;
        slots[i].field4  = 0;
        slots[i].field8  = 0;
        slots[i].fieldC  = 0;
        slots[i].field10 = 0;
    }
    // Zero the extra int at the end of the structure
    extraInt = 0;
}