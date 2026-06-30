// FUNC_NAME: Camera::constructor
// Based on decompilation at 0x00552280 – initializes a Camera object with multiple inheritance
// Sets up vtable pointers, and many fields to 0 or 0x80000000 (sentinel/infinite values)

#include <cstdint>

// External vtable symbols from the data section
extern void *PTR_FUN_00e39fb0;   // primary vtable at offset 0
extern void *PTR_LAB_00dc3dd4;   // base vtable for first base (offset 8)
extern void *PTR_LAB_00e39f9c;   // base vtable for second base (offset 12)
extern void *PTR_LAB_00e39fc8;   // derived vtable override first base
extern void *PTR_LAB_00e39fdc;   // derived vtable override second base

// Forward declare the secondary init function
void FUN_005523c0(void);

// Camera struct layout (partial, offsets in hex)
struct Camera {
    union {                         // +0x00: primary vtable pointer
        void *primaryVtable;
        uint32_t field_0x00;
    };
    // +0x04: padding (or another 4-byte field)
    uint16_t field_0x06;            // +0x06: short set to 1
    // +0x08: vtable pointer for first base class
    void *vtable1;                  // offset +0x08
    // +0x0C: vtable pointer for second base class
    void *vtable2;                  // offset +0x0C
    // +0x10..+0x2F: unknown (not touched by this function)
    uint32_t field_0x30;            // +0x30 (index 12)
    // +0x34..+0x60: unknown
    uint32_t field_0x64;            // +0x64 (index 25)
    uint32_t field_0x68;            // +0x68 (index 26)
    uint32_t field_0x6C;            // +0x6C (index 27) – initialized to 0x80000000
    uint32_t field_0x70;            // +0x70 (index 28)
    uint32_t field_0x74;            // +0x74 (index 29)
    uint32_t field_0x78;            // +0x78 (index 30) – 0x80000000
    uint32_t field_0x7C;            // +0x7C (index 31)
    uint32_t field_0x80;            // +0x80 (index 32)
    uint32_t field_0x84;            // +0x84 (index 33) – 0x80000000
    uint32_t field_0x88;            // +0x88 (index 34)
    uint32_t field_0x8C;            // +0x8C (index 35)
    uint32_t field_0x90;            // +0x90 (index 36) – 0x80000000
};

// Constructor (__thiscall, ECX = this)
void __thiscall Camera::constructor(Camera *this)
{
    // Set small type/version field to 1
    *(int16_t *)((uint8_t *)this + 6) = 1;

    // Initialize base vtable pointers (first assignment – base class vtables)
    this->vtable1 = &PTR_LAB_00dc3dd4;   // +0x08
    this->vtable2 = &PTR_LAB_00e39f9c;   // +0x0C

    // Set primary vtable (offset 0x00)
    this->primaryVtable = &PTR_FUN_00e39fb0;

    // Override base vtables with derived class vtables (final vtables)
    this->vtable1 = &PTR_LAB_00e39fc8;   // +0x08
    this->vtable2 = &PTR_LAB_00e39fdc;   // +0x0C

    // Initialize fields – pattern: groups of three 4-byte values, some set to 0x80000000 (sentinel)
    // Possibly representing a bounding box or vector components with infinite/empty state
    this->field_0x30 = 0;
    this->field_0x64 = 0;
    this->field_0x68 = 0;
    this->field_0x6C = 0x80000000;   // sentinel value
    this->field_0x70 = 0;
    this->field_0x74 = 0;
    this->field_0x78 = 0x80000000;
    this->field_0x7C = 0;
    this->field_0x80 = 0;
    this->field_0x84 = 0x80000000;
    this->field_0x88 = 0;
    this->field_0x8C = 0;
    this->field_0x90 = 0x80000000;

    // Secondary initialization (likely virtual or inlined)
    FUN_005523c0();
    return;
}