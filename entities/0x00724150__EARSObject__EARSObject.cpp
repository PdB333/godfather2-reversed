// FUNC_NAME: EARSObject::EARSObject
// Address: 0x00724150
// Role: Constructor for a base EA EARS object, initializes vtable pointers and debug sentinel values.
// This pattern is typical for EA's debug memory initialization with sentinel markers.

class EARSObject {
public:
    // Vtable pointer at +0x0
    // Second vtable pointer (likely for derived interface) at +0x3C
    // Fields +0x4 to +0x1C: zeroed
    // Fields +0x20 to +0x2C: set to sentinel values then cleared
    // Fields +0x30 to +0x38: zeroed
    // Field +0x3C: pointer to second vtable
    // Field +0x40: zeroed
    // Fields +0x44 to +0x50: zeroed via 8-byte writes
    // Field +0x54: zeroed
    // Field +0x58: copied from global DAT_00d58cbc

    void __thiscall constructor() {
        // Clear members 1-7 (offsets 0x04 to 0x1C)
        this->field_0x04 = 0;
        this->field_0x08 = 0;
        this->field_0x0C = 0;
        this->field_0x10 = 0;
        this->field_0x14 = 0;
        this->field_0x18 = 0;
        this->field_0x1C = 0;

        // Initialize sentinel markers for debug (offsets 0x20, 0x24, 0x28, 0x2C)
        this->sentinel1 = 0xBADBADBA;
        this->sentinel2 = 0xBEEFBEEF;
        this->sentinel3 = 0xEAC15A55;
        this->sentinel4 = 0x91100911;

        // Clear members 0x0C to 0x0E (offsets 0x30, 0x34, 0x38)
        this->field_0x30 = 0;
        this->field_0x34 = 0;
        this->field_0x38 = 0;

        // Clear sentinel markers (reuse same fields)
        this->sentinel1 = 0;
        this->sentinel2 = 0;
        this->sentinel3 = 0;
        this->sentinel4 = 0;

        // Set second vtable pointer at offset 0x3C
        this->secondVtable = &PTR_FUN_00e32808; // initial
        // Set main vtable at offset 0x00
        this->vtable = &PTR_FUN_00d620c8;
        // Update second vtable pointer to final value
        this->secondVtable = &PTR_LAB_00d620c4;

        // Zero out 8 bytes at offsets 0x44 and 0x4C (fields 0x11-0x14)
        *(unsigned long long*)(&this->field_0x44) = 0;
        *(unsigned long long*)(&this->field_0x4C) = 0;

        // Clear field at offset 0x54
        this->field_0x54 = 0;

        // Copy global value to offset 0x58
        this->field_0x58 = DAT_00d58cbc;
    }

private:
    // Members (offsets in bytes)
    void* vtable;                          // +0x00
    int field_0x04;                        // +0x04
    int field_0x08;                        // +0x08
    int field_0x0C;                        // +0x0C
    int field_0x10;                        // +0x10
    int field_0x14;                        // +0x14
    int field_0x18;                        // +0x18
    int field_0x1C;                        // +0x1C
    int sentinel1;                         // +0x20
    int sentinel2;                         // +0x24
    int sentinel3;                         // +0x28
    int sentinel4;                         // +0x2C
    int field_0x30;                        // +0x30
    int field_0x34;                        // +0x34
    int field_0x38;                        // +0x38
    void* secondVtable;                    // +0x3C
    int field_0x40;                        // +0x40
    long long field_0x44;                  // +0x44 (8 bytes)
    long long field_0x4C;                  // +0x4C (8 bytes)
    int field_0x54;                        // +0x54
    int field_0x58;                        // +0x58
};

// External symbols referenced
extern int DAT_00d58cbc;
extern void* PTR_FUN_00e32808;
extern void* PTR_FUN_00d620c8;
extern void* PTR_LAB_00d620c4;