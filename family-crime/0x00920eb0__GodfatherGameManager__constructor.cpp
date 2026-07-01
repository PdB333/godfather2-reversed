// FUNC_NAME: GodfatherGameManager::constructor
// Address: 0x00920eb0
// GodfatherGameManager constructor. Initializes singleton, allocates sub-buffer, zeroes fields.
// Struct offsets documented in comments.

#include <cstdint>

// Base class constructor (likely sets initial vtable and base fields)
void __fastcall baseClassConstructor(GodfatherGameManager* this_);

// Memory allocation (size in bytes, returns pointer)
void* __fastcall memoryAllocate(uint32_t size);

// Global singleton pointer
GodfatherGameManager* g_pGodfatherGameManager; // DAT_0112e2e8

struct GodfatherGameManager {
    // Vtable pointer at +0x00
    void** vtable;               // +0x00: set to PTR_FUN_00d86320

    // Field at +0x04: pointer or other data
    void* field_0x04;            // +0x04: set to PTR_LAB_00d862fc

    // Padding or other fields from base class at +0x08 to +0x4F? (not touched here)
    uint8_t pad_0x08_to_0x4F[0x50 - 0x08]; // placeholder

    // Offset +0x50: first vtable-like pointer (overridden)
    void* vtable2;               // +0x50: set to PTR_LAB_00d862f8 (final)

    // Offset +0x54: second vtable-like pointer (overridden)
    void* vtable3;               // +0x54: set to PTR_LAB_00d862e0 (final)

    // Offsets +0x58 to +0x7C: zeroed
    uint32_t zero58;             // +0x58
    uint32_t zero5C;             // +0x5C
    uint32_t zero60;             // +0x60
    uint32_t zero64;             // +0x64
    uint32_t zero68;             // +0x68
    uint32_t zero6C;             // +0x6C
    uint32_t zero70;             // +0x70
    uint32_t zero74;             // +0x74
    uint32_t zero78;             // +0x78
    uint32_t zero7C;             // +0x7C

    // Offset +0x80: zeroed
    uint32_t field_0x80;         // +0x80

    // Offset +0x84: zeroed
    uint32_t field_0x84;         // +0x84

    // Padding/other fields +0x88 to +0x93
    uint8_t pad_0x88_to_0x93[0x94 - 0x88];

    // Offset +0x94: zeroed? Not explicitly set but might be from base? Actually not set here.
    // But +0x98 is set.

    // Offset +0x98: allocated buffer (0x40 bytes)
    uint8_t* allocatedBuffer;    // +0x98: from memoryAllocate(0x40)

    // Offset +0x9C: zeroed
    uint32_t zero9C;             // +0x9C

    // Offsets +0xA0, +0xA1: byte zero fields
    uint8_t byteA0;              // +0xA0
    uint8_t byteA1;              // +0xA1

    // Offsets +0xA2, +0xA3: padding? Not set.

    // Offset +0xA4: zeroed
    uint32_t zeroA4;             // +0xA4

    // Offset +0xA8: zeroed
    uint32_t zeroA8;             // +0xA8

    // Offset +0xAC: byte zero
    uint8_t byteAC;              // +0xAC
};

// Constructor implementation
GodfatherGameManager* __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this_) {
    // Call base class constructor (FUN_00957ed0)
    baseClassConstructor(this_);

    // Set vtable pointer for this class
    this_->vtable = &PTR_FUN_00d86320; // +0x00

    // Store this as global singleton
    g_pGodfatherGameManager = this_;

    // Set initial vtable2 and vtable3 (later overwritten; probably base class defaults)
    this_->vtable2 = &PTR_LAB_00d862dc; // +0x50
    this_->vtable3 = &PTR_LAB_00d84f98; // +0x54

    // Override vtable2 and vtable3 to actual class vtables
    this_->vtable2 = &PTR_LAB_00d862f8; // +0x50
    this_->vtable3 = &PTR_LAB_00d862e0; // +0x54

    // Zero out fields from +0x58 to +0x74
    this_->zero58 = 0;
    this_->zero5C = 0;
    this_->zero60 = 0;
    this_->zero64 = 0;
    this_->zero68 = 0;
    this_->zero6C = 0;
    this_->zero70 = 0;
    this_->zero74 = 0;

    // Zero out fields at +0x78, +0x7C, +0x80, +0x84
    this_->zero78 = 0;
    this_->zero7C = 0;
    this_->field_0x80 = 0;

    // Zero at +0x9C
    this_->zero9C = 0;

    // Zero byte at +0xA0
    this_->byteA0 = 0;

    // Zero byte at +0xA1
    this_->byteA1 = 0;

    // Zero at +0xA4, +0xA8
    this_->zeroA4 = 0;
    this_->zeroA8 = 0;

    // Zero byte at +0xAC
    this_->byteAC = 0;

    // Allocate 0x40 bytes and store at +0x98
    this_->allocatedBuffer = (uint8_t*)memoryAllocate(0x40);

    // Initialize first byte of allocatedBuffer to 0
    *this_->allocatedBuffer = 0;

    // Set fields at +0x80 and +0x78, +0x7C? Already zeroed above but there's additional zeroing:
    // Actually the decompiled code shows: param_1[0x20] = 0; param_1[0x1e] = 0; param_1[0x1f] = 0;
    // But we already zeroed those (0x80, 0x78, 0x7C). So it's redundant but fine.

    return this_;
}