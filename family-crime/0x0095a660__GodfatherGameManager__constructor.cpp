// FUNC_NAME: GodfatherGameManager::constructor
// Function address: 0x0095a660
// Role: Constructor for the GodfatherGameManager singleton. Initializes vtable pointers,
// zeroes many member fields, and allocates a small 2-byte buffer (likely for flags or state).

GodfatherGameManager* __thiscall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Base class constructor (e.g., EARS::Framework::Singleton)
    SomeBase::constructor();

    // Temporary vtable pointer at offset +0x4C (0x13 * 4)
    this->field_0x4C = &g_unknownVtable1;  // PTR_LAB_00d8c8c4

    // Store global instance pointer
    g_GodfatherGameManager = this;          // DAT_011307e8

    // Main vtable at offset 0x00
    this->vtable = &g_vtable_GodfatherGameManager;  // PTR_FUN_00d8c8f0

    // Secondary interface pointer at offset +0x10 (0x4 * 4)
    this->field_0x10 = &g_unknownVtable2;   // PTR_LAB_00d8c8cc

    // Update vtable at offset +0x4C to derived class vtable
    this->field_0x4C = &g_unknownVtable3;   // PTR_LAB_00d8c8c8

    // Zero-initialize counters/pointers at offsets +0x50..+0x64
    this->field_0x50 = 0;  // param_1[0x14]
    this->field_0x54 = 0;  // param_1[0x15]
    this->field_0x58 = 0;  // param_1[0x16]
    this->field_0x5C = 0;  // param_1[0x17]
    this->field_0x60 = 0;  // param_1[0x18]
    this->field_0x64 = 0;  // param_1[0x19]

    // Another pointer/table at offset +0x68 (0x1A * 4)
    this->field_0x68 = &g_unknownVtable4;   // PTR_LAB_00d83b18

    // Zero more fields from +0xEC to +0xF8
    this->field_0xEC = 0;  // param_1[0x3B]
    this->field_0xF0 = 0;  // param_1[0x3C]
    this->field_0xF4 = 0;  // param_1[0x3D]
    this->field_0xF8 = 0;  // param_1[0x3E]

    // Set boolean flag at offset +0xFC to 1 (enabled)
    *(uint8_t*)((uint8_t*)this + 0xFC) = 1;  // *(undefined1*)(param_1 + 0x3F) = 1

    // Zero fields from +0x100 to +0x128
    this->field_0x100 = 0; // param_1[0x40]
    this->field_0x104 = 0; // param_1[0x41]
    this->field_0x108 = 0; // param_1[0x42]
    this->field_0x10C = 0; // param_1[0x43]
    this->field_0x110 = 0; // param_1[0x44]
    this->field_0x114 = 0; // param_1[0x45]
    this->field_0x118 = 0; // param_1[0x46]
    this->field_0x11C = 0; // param_1[0x47]
    this->field_0x120 = 0; // param_1[0x48]
    this->field_0x124 = 0; // param_1[0x49]
    this->field_0x128 = 0; // param_1[0x4A]

    // Cleared pointer at offset +0x12C? Actually param_1[0x4B] is +0x12C, but decompiler shows
    // param_1[0x4B] = 0? Not shown? Wait, decompiled shows: param_1[0x4b] = 0; Yes it is there.
    this->field_0x12C = 0; // param_1[0x4B]

    // Zero a byte at offset +0x134 (4 * 0x4D)
    *(uint8_t*)((uint8_t*)this + 0x134) = 0;  // *(undefined1*)(param_1 + 0x4D) = 0

    // Allocate a 2-byte buffer (likely for message or state flags)
    uint8_t* buffer = (uint8_t*)FUN_009c8e80(2); // allocate(2)
    this->smallBuffer = buffer;  // param_1[0x4C] at offset +0x130

    // Zero the two bytes
    buffer[1] = 0;
    buffer[0] = 0;

    return this;
}