// FUNC_NAME: CPlayerSlotArray::InitializeSlots
#pragma pack(push, 1)
struct CPlayerSlot {
    void* vtable;                // +0x00
    int field_04;                // +0x04
    int field_08;                // +0x08
    int zeroArray[15];           // +0x0C..0x44 (15 dwords)
    short field_48;              // +0x48
    short field_4A;              // +0x4A
    int   field_4C;              // +0x4C
    short field_50;              // +0x50
    short field_52;              // +0x52
    int   field_54;              // +0x54
    short field_58;              // +0x58
    short field_5A;              // +0x5A
    int   field_5C;              // +0x5C
    short field_60;              // +0x60
    short field_62;              // +0x62
    int   maxValue;              // +0x64 (initialized to 100)
    char  field_68;              // +0x68
    char  pad[3];                // +0x69..0x6B (padding)
};
#pragma pack(pop)

// Class containing an array of 8 slots and a count field
class CPlayerSlotArray {
public:
    CPlayerSlot slots[8];        // +0x000
    int slotCount;               // +0x360
};

void __fastcall CPlayerSlotArray::InitializeSlots(CPlayerSlotArray* this) {
    CPlayerSlot* slot = &this->slots[0];
    for (int i = 0; i < 8; ++i) {
        // Set vtable pointer for this slot
        slot->vtable = reinterpret_cast<void*>(0x00d5d9b0);
        slot->field_04 = 0;
        slot->field_08 = 0;

        // Zero the 15 dword array
        for (int j = 0; j < 15; ++j) {
            slot->zeroArray[j] = 0;
        }

        // Initialize word/dword fields to zero
        slot->field_48 = 0;
        slot->field_4A = 0;
        slot->field_4C = 0;
        slot->field_50 = 0;
        slot->field_52 = 0;
        slot->field_54 = 0;
        slot->field_58 = 0;
        slot->field_5A = 0;
        slot->field_5C = 0;
        slot->field_60 = 0;
        slot->field_62 = 0;

        // Set a maximum value (default 100)
        slot->maxValue = 100;

        // Last byte in the slot (set to 0)
        slot->field_68 = 0;

        // Move to the next slot (each slot is 0x6C bytes)
        ++slot;
    }

    // Final field at offset 0x360 (initialized to 0)
    this->slotCount = 0;
}