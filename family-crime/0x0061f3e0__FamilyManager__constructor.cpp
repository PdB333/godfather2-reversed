// FUNC_NAME: FamilyManager::constructor

extern int* g_someFunctionTable; // DAT_00e2b1a4 - pointer to function table for family subsystem
extern void* PTR_FUN_00e41380; // vtable for FamilyManager

class FamilyManager {
public:
    // Vtable at offset 0x00
    void* vtable;

    // --- Family data: 4 slots (for 4 families) ---
    // Each entry: function table pointer + 4 unknown ints (5 ints total = 20 bytes)
    struct FamilyEntry {
        int* funcTable; // +0x00
        int unk1;       // +0x04
        int unk2;       // +0x08
        int unk3;       // +0x0C
        int unk4;       // +0x10
    };

    // Array of 4 family entries at int offset 0x1c (byte 0x70)
    FamilyEntry familyEntries[4]; // occupies ints 0x1c..0x2f

    // Fields beyond the family entries (int offset 0x30 = byte 0xC0)
    int field_0x30; // +0xC0
    int field_0x31; // +0xC4
    int field_0x32; // +0xC8
    int field_0x33; // +0xCC
    int field_0x34; // +0xD0
    short lowWord_0x35; // +0xD4 (lower 16 bits of int at offset 0x35)
    short highWord_0x35; // +0xD6 (upper 16 bits)
    short lowWord_0x36; // +0xD8 (lower 16 bits of int at offset 0x36)
    short highWord_0x36; // +0xDA (upper 16 bits)
    int field_0x37; // +0xDC

    void constructor();
};

void FamilyManager::constructor() {
    int* uVar1 = g_someFunctionTable;

    // Set vtable
    this->vtable = &PTR_FUN_00e41380;

    // Initialize family entry 0 (int offset 0x1c)
    this->familyEntries[0].funcTable = uVar1;
    this->familyEntries[0].unk1 = 0;
    this->familyEntries[0].unk2 = 0;
    this->familyEntries[0].unk3 = 0;
    this->familyEntries[0].unk4 = 0;

    // Family entry 1 (int offset 0x21)
    this->familyEntries[1].funcTable = uVar1;
    this->familyEntries[1].unk1 = 0;
    this->familyEntries[1].unk2 = 0;
    this->familyEntries[1].unk3 = 0;
    this->familyEntries[1].unk4 = 0;

    // Family entry 2 (int offset 0x26)
    this->familyEntries[2].funcTable = uVar1;
    this->familyEntries[2].unk1 = 0;
    this->familyEntries[2].unk2 = 0;
    this->familyEntries[2].unk3 = 0;
    this->familyEntries[2].unk4 = 0;

    // Family entry 3 (int offset 0x2b)
    this->familyEntries[3].funcTable = uVar1;
    // Only first three unk fields zeroed; unk4 left uninitialized (matches decompiled)
    this->familyEntries[3].unk1 = 0;
    this->familyEntries[3].unk2 = 0;
    this->familyEntries[3].unk3 = 0;
    // Note: familyEntries[3].unk4 not set to zero

    // Zero fields from 0x30 onward
    this->field_0x30 = 0;
    this->field_0x31 = 0;
    this->field_0x32 = 0;
    this->field_0x33 = 0;
    this->field_0x34 = 0;
    this->lowWord_0x35 = 0;
    this->highWord_0x35 = 0;
    this->lowWord_0x36 = 0;
    this->highWord_0x36 = 0;
    this->field_0x37 = 0;
}