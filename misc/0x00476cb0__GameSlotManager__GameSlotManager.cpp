// FUNC_NAME: GameSlotManager::GameSlotManager
// Function at 0x00476cb0 - Constructor for a slot-based manager (likely player/controller slots)
// Initializes 8 slots with sequential IDs and zeroes out state fields.
GameSlotManager::GameSlotManager(uint baseObject) {
    // Call base class constructor with the provided parameter (possibly parent object)
    FUN_0046c590(baseObject);

    // Set vtable pointers (three virtual function tables)
    this->vtable0 = &PTR_FUN_00e32f00;          // +0x00: primary vtable
    this->vtable2 = &PTR_LAB_00e32f1c;          // +0x3C (0xF*4): secondary vtable
    this->vtable3 = &PTR_LAB_00e32f2c;          // +0x48 (0x12*4): tertiary vtable

    // Initialize first set of fields (slot 0 state?)
    this->field0x50 = 0;                        // +0x50: 4-byte field
    *(uint16*)((char*)this + 0x54) = 0;         // +0x54: 2-byte field
    *(uint16*)((char*)this + 0x56) = 0;         // +0x56: 2-byte field

    this->field0x58 = 0;                        // +0x58: 4-byte field
    this->field0x5C = 0xFFFFFFFF;               // +0x5C: 4-byte field, initialized to -1
    this->field0x60 = 0;                        // +0x60: 4-byte field
    *(uint16*)((char*)this + 0x64) = 0;         // +0x64: 2-byte field
    *(uint16*)((char*)this + 0x66) = 0;         // +0x66: 2-byte field

    // Initialize slot-specific fields (8 slots)
    // Each slot appears to have a 4-byte field followed by two 2-byte fields.
    this->slot0.field0x68 = 0;                  // +0x68
    *(uint16*)((char*)this + 0x6C) = 0;         // +0x6C
    *(uint16*)((char*)this + 0x6E) = 0;         // +0x6E

    this->slot1.field0x70 = 0;                  // +0x70
    *(uint16*)((char*)this + 0x74) = 0;         // +0x74
    *(uint16*)((char*)this + 0x76) = 0;         // +0x76

    this->slot2.field0x80 = 0;                  // +0x80
    *(uint16*)((char*)this + 0x84) = 0;         // +0x84
    *(uint16*)((char*)this + 0x86) = 0;         // +0x86

    this->slot3.field0x90 = 0;                  // +0x90
    *(uint16*)((char*)this + 0x94) = 0;         // +0x94
    *(uint16*)((char*)this + 0x96) = 0;         // +0x96

    this->slot4.field0xA0 = 0;                  // +0xA0
    *(uint16*)((char*)this + 0xA4) = 0;         // +0xA4
    *(uint16*)((char*)this + 0xA6) = 0;         // +0xA6

    this->slot5.field0xB0 = 0;                  // +0xB0
    *(uint16*)((char*)this + 0xB4) = 0;         // +0xB4
    *(uint16*)((char*)this + 0xB6) = 0;         // +0xB6

    this->slot6.field0xC0 = 0;                  // +0xC0
    *(uint16*)((char*)this + 0xC4) = 0;         // +0xC4
    *(uint16*)((char*)this + 0xC6) = 0;         // +0xC6

    this->slot7.field0xD0 = 0;                  // +0xD0
    *(uint16*)((char*)this + 0xD4) = 0;         // +0xD4
    *(uint16*)((char*)this + 0xD6) = 0;         // +0xD6

    // Initialize another set of 8 fields with sequential IDs (starting from 1)
    // These are at offsets 0x6C, 0x70, 0x74, ... (overlaps partially with above)
    for (int i = 1; i <= 8; i++) {
        // piVar1 points to field at 0x1B + (i-1)*4 (in int units)
        int* pField = (int*)((char*)this + 0x6C + (i-1)*4);
        *pField = i;                          // Set ID
        *(pField + 3) = 0;                    // Set field at +12 bytes to 0
    }

    return;
}