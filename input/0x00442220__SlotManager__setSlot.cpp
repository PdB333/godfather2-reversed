// FUNC_NAME: SlotManager::setSlot

// Reconstructed from 0x00442220 - sets a slot's value and calls initializer
// Structure layout (offsets relative to this):
// +0x20: int slotCount
// +0x24: Slot* slots (array of Slot objects, each 0x14 bytes)
// Slot layout (each 0x14 bytes):
// +0x00: unknown
// +0x04: unknown
// +0x08: int value / handle (the field written here)
// +0x0C: unknown
// +0x10: unknown

struct Slot {
    int field_0x00;
    int field_0x04;
    int value;        // +0x08
    int field_0x0C;
    int field_0x10;
};

class SlotManager {
public:
    int slotCount;      // +0x20
    Slot* slots;        // +0x24

    // __fastcall: param_1 = this (via ECX), slotIndex in EAX, value in EDI
    void __fastcall setSlot(int slotIndex, int value);
    void __fastcall initializeSlot(int slotIndex);  // FUN_00442240
};

void __fastcall SlotManager::setSlot(int slotIndex, int value) {
    if (slotIndex >= 0 && slotIndex < this->slotCount) {
        this->slots[slotIndex].value = value;
        this->initializeSlot(slotIndex);
    }
}