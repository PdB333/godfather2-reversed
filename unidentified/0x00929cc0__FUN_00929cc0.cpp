// FUNC_NAME: SomeClass::constructor
// Address: 0x00929cc0
// Role: Constructor for a singleton manager class, sets up vtable and initializes fields to zero.
// Calls base class constructor at FUN_005bf9b0, then configures multiple vtable pointers and global singleton.

class SomeClass;

// Global singleton pointer
extern SomeClass* g_pSomeClass; // DAT_0112a9cc

// VTable and data labels (external symbols from the game binary)
extern void* PTR_FUN_00d85ee0; // Primary vtable
extern void* PTR_LAB_00d85eb8; // Secondary vtable or data
extern void* PTR_LAB_00d85eb4; // Override for offset 0x4C
extern void* PTR_LAB_00d85d7c; // Initial vtable for offset 0x4C (set then overwritten)

// Base class constructor
void __fastcall baseClassConstructor(SomeClass* this); // FUN_005bf9b0

// __fastcall: this in ECX, no other parameters
SomeClass* __fastcall SomeClass::constructor(SomeClass* this)
{
    baseClassConstructor(this); // Call base class constructor

    // Set initial vtable at offset 0x4C (0x13 * 4)
    this->field_0x4C = &PTR_LAB_00d85d7c;

    // Store singleton pointer
    g_pSomeClass = this; // DAT_0112a9cc

    // Zero out bytes at offsets 0x50 and 0x51
    this->byte_0x50 = 0;
    this->byte_0x51 = 0;

    // Zero out integers at offsets 0x54, 0x58, 0x5C, 0x60
    this->field_0x54 = 0;
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x60 = 0;

    // Set primary vtable at offset 0
    this->vtable = &PTR_FUN_00d85ee0;

    // Set another vtable at offset 0x10 (4th pointer)
    this->field_0x10 = &PTR_LAB_00d85eb8;

    // Override vtable at offset 0x4C
    this->field_0x4C = &PTR_LAB_00d85eb4;

    return this;
}