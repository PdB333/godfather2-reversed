// FUNC_NAME: EARSObject::EARSObject

// Constructor for a base game object in EARS engine.
// Initializes vtable pointers, debug markers, and flags.
// Calls base class initializer at 0x0046c590.

struct EARSObject {
    // offset 0x00: primary vtable pointer
    void** vtable;
    // ... (other fields up to 0x3C)
    void* vtable2; // +0x3C
    void* vtable3; // +0x48
    uint32_t field_0x50; // +0x50
    uint16_t field_0x54; // +0x54
    uint16_t field_0x56; // +0x56
    uint32_t field_0x58; // +0x58
    uint16_t field_0x5C; // +0x5C
    uint16_t field_0x5E; // +0x5E
    uint32_t debugMarker1; // +0x60, initially 0xBADBADBA
    uint32_t debugMarker2; // +0x64, initially 0xBEEFBEEF
    uint32_t debugMarker3; // +0x68, initially 0xEAC15A55
    uint32_t debugMarker4; // +0x6C, initially 0x91100911
    uint32_t field_0x70; // +0x70
    uint32_t field_0x74; // +0x74
    uint8_t field_0x78; // +0x78
    uint8_t field_0x79; // +0x79
    uint8_t field_0x7A; // +0x7A, set to 1
};

void __thiscall EARSObject::EARSObject(uint32_t param) {
    // Call base class constructor (0x0046c590)
    FUN_0046c590(param);

    // Set vtable pointers for multiple inheritance
    this->vtable = (void**)&PTR_FUN_00e332d4;   // primary vtable
    this->vtable2 = (void**)&PTR_LAB_00e332f8;  // secondary vtable
    this->vtable3 = (void**)&PTR_LAB_00e33308;  // tertiary vtable

    // Zero out initial fields
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x56 = 0;
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x5E = 0;

    // Initialize debug marker fields with distinctive patterns
    this->debugMarker1 = 0xBADBADBA;
    this->debugMarker2 = 0xBEEFBEEF;
    this->debugMarker3 = 0xEAC15A55;
    this->debugMarker4 = 0x91100911;

    // Zero out additional fields
    this->field_0x70 = 0;
    this->field_0x74 = 0;
    this->field_0x78 = 0;
    this->field_0x79 = 0;
    this->field_0x7A = 1;  // set to 1 after clearing

    // Clear the debug markers (re-initialize to zero)
    this->debugMarker1 = 0;
    this->debugMarker2 = 0;
    this->debugMarker3 = 0;
    this->debugMarker4 = 0;
}