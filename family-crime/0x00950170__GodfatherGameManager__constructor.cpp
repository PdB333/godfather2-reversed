// FUNC_NAME: GodfatherGameManager::constructor
// Address: 0x00950170
// Role: Constructor for GodfatherGameManager singleton. Initializes base class, sets vtable pointers, zeroes fields, and stores instance globally.

// Note: This function is __fastcall, with 'this' in ECX.
// Base constructor at 0x005bf9b0 is called first (likely EARSObject or similar).
// Global pointer DAT_01130004 stores the singleton instance.

GodfatherGameManager* __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Call base class constructor (likely EARSObject or Entity)
    // FUN_005bf9b0 is assumed to be the base constructor; it may set initial vtable pointers.
    FUN_005bf9b0(); // Base constructor call (this pointer implicitly passed in ECX)

    // Set initial vtable pointer for base class? (offset +0x4C)
    this->field_0x4C = &PTR_LAB_00d8bafc; // +0x4C: base class vtable or interface pointer

    // Store this instance globally (singleton)
    DAT_01130004 = this; // Global pointer to GodfatherGameManager instance

    // Zero out fields at offsets +0x50, +0x54, and byte at +0x58
    this->field_0x50 = 0; // +0x50: some member (int)
    this->field_0x54 = 0; // +0x54: some member (int)
    *(uint8_t*)((uint8_t*)this + 0x58) = 0; // +0x58: byte member

    // Set vtable pointer for this class (offset +0x00)
    this->vtable = &PTR_FUN_00d8bb28; // +0x00: primary vtable

    // Set secondary vtable or interface pointer (offset +0x10)
    this->field_0x10 = &PTR_LAB_00d8bb04; // +0x10: secondary vtable

    // Override the field at +0x4C with derived class vtable/interface pointer
    this->field_0x4C = &PTR_LAB_00d8bb00; // +0x4C: derived class vtable or interface

    return this;
}