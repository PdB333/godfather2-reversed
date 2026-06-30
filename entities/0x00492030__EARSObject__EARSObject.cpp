// FUNC_NAME: EARSObject::EARSObject
// Function at 0x00492030 - Constructor for base EARSObject (EA engine)
// Initializes vtable, zeroes many fields, sets up two sub-structures (likely input slots or controllers)

#include <cstdint>

// Global constants used for initializing fields
extern uint32_t g_someConstant1; // DAT_00e2b1a4
extern uint32_t g_someConstant2; // DAT_00e44628

class EARSObject {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // Fields at various offsets (documented as +0x70, +0x78-0x7f, +0x80-0xbf, etc.)
    uint32_t field_0x70;     // +0x70
    uint32_t field_0x78[8];  // +0x78 to +0x7f (8 dwords)

    // Two sub-structures of 16 dwords each (indices 0x80-0x93 and 0x94-0xA3)
    struct SubBlock {
        uint32_t pad[16];    // actually has specific pattern, but we treat as opaque
    };
    SubBlock sub1;           // +0x80 (indices 0x80-0x93)
    SubBlock sub2;           // +0x94 (indices 0x94-0xA3) but note overlap in loop

    uint32_t field_0xa4;     // +0xa4
    uint32_t field_0xa5;     // +0xa5
    uint32_t field_0xa6;     // +0xa6
    uint32_t field_0xa7;     // +0xa7
    uint32_t field_0xa8;     // +0xa8
    uint32_t field_0xa9;     // +0xa9
    uint32_t field_0xaa;     // +0xaa
    uint32_t field_0xab;     // +0xab
    uint64_t field_0xad;     // +0xad (8 bytes)
    uint32_t field_0xb0;     // +0xb0
    uint32_t field_0xb1;     // +0xb1
    uint32_t field_0xb2;     // +0xb2
    uint32_t field_0xb3;     // +0xb3

    void __thiscall constructor();
};

// Decompiled constructor
void EARSObject::constructor() {
    // Call base class constructor
    // (Implementation at 0x00490560)
    baseConstructor(); // placeholder for FUN_00490560

    // Set vtable pointer
    this->vtable = &g_VTable_EARSObject; // PTR_LAB_00e34490

    // Zero out fields at specific offsets (using in_EAX = this)
    this->field_0x70 = 0;
    this->field_0xa4 = 0;
    this->field_0xa7 = 0;
    this->field_0xac = 0;
    this->field_0x78[0] = 0; // +0x78
    this->field_0x78[1] = 0; // +0x7c
    this->field_0x78[2] = 0; // +0x79
    this->field_0x78[3] = 0; // +0x7d
    this->field_0x78[4] = 0; // +0x7a
    this->field_0x78[5] = 0; // +0x7e
    this->field_0x78[6] = 0; // +0x7b
    this->field_0x78[7] = 0; // +0x7f

    // Initialize two sub-blocks with pattern:
    // Each sub-block spans indices 0x80..0x93 and 0x94..0xA3 (but offset by 0x10 in loop)
    uint32_t* ptrBlockBase = &this->field_0x80; // start of sub1 (address of field_0x80)
    uint32_t* ptrFar = &this->field_0x8c;       // start of sub1 + 0x0c (indices 0x8c)
    int iter = 2;
    do {
        // Zero out the first dword of this sub-block (index 0x80 then 0x81)
        *ptrBlockBase = 0;

        // Set pattern for indices 0x84-0x93 (first iter) then 0x94-0xA3 (second iter)
        // Each pattern: set specific fields to g_someConstant1 or 0
        *(ptrFar - 8) = g_someConstant1; // index 0x84
        *(ptrFar - 7) = 0;               // index 0x85
        *(ptrFar - 6) = 0;               // index 0x86
        *(ptrFar - 5) = 0;               // index 0x87
        *(ptrFar - 4) = 0;               // index 0x88
        *(ptrFar - 3) = g_someConstant1; // index 0x89
        *(ptrFar - 2) = 0;               // index 0x8a
        *(ptrFar - 1) = 0;               // index 0x8b
        *ptrFar = 0;                     // index 0x8c
        *(ptrFar + 1) = 0;               // index 0x8d
        *(ptrFar + 2) = g_someConstant1; // index 0x8e
        *(ptrFar + 3) = 0;               // index 0x8f
        *(ptrFar + 4) = 0;               // index 0x90
        *(ptrFar + 5) = 0;               // index 0x91
        *(ptrFar + 6) = 0;               // index 0x92
        *(ptrFar + 7) = g_someConstant1; // index 0x93

        // Advance to next sub-block
        ptrBlockBase++;
        ptrFar += 0x10; // move by 16 dwords (64 bytes)
        iter--;
    } while (iter != 0);

    // Note: indices 0x82 and 0x83 remain uninitialized (likely zero from previous state)

    // Set remaining fields
    this->field_0xa5 = g_someConstant2;
    this->field_0xa6 = g_someConstant2;
    this->field_0xab = 0;
    this->field_0xaa = 0;
    this->field_0xa9 = 0;
    this->field_0xa8 = 0;

    // Zero 8 bytes at +0xad
    *reinterpret_cast<uint64_t*>(&this->field_0xad) = 0;

    // Zero fields at +0xb0..+0xb3
    this->field_0xb3 = 0;
    this->field_0xb2 = 0;
    this->field_0xb1 = 0;
    this->field_0xb0 = 0;
}
```