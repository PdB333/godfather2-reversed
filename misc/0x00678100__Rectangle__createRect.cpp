// FUNC_NAME: Rectangle::createRect
// Address: 0x00678100
// This function allocates and initializes a Rectangle object (size 0x78 bytes)
// containing a sub-struct (size 0x34 bytes) with short fields initialized from parameters.
// param_1 is likely a parent/owner pointer, param_2-param_4 are rectangle dimensions.

#include <cstdint>

// Forward declaration of memory allocation function
void* __cdecl allocate(int size); // corresponds to FUN_00672f60

struct RectSubData {
    uint8_t unknown0[0x20];      // 32 bytes, not directly initialized here
    short val20;                 // +0x20
    short val22;                 // +0x22 = param2
    short val24;                 // +0x24 = 0
    short val26;                 // +0x26 = 0
    short val28;                 // +0x28 = 0
    short val2A;                 // +0x2A = 0
    short val2C;                 // +0x2C = param3
    short val2E;                 // +0x2E = param3 - param4
    // Total 32 + 14 = 46 bytes, remainder up to 0x34 (52 bytes) unknown
};

struct Rectangle {
    void* parent;                // +0x00 = param_1
    short field_4;               // +0x04 = 0
    int field_8;                 // +0x08 = 0 (set later)
    int field_C;                 // +0x0C = 0
    int field_10;                // +0x10 = 0
    short field_34;              // +0x34 = 2 (type flag?)
    // ... more fields up to 0x78
    void* subPtr0;               // +0x44? Actually indexed offsets:
    // Actually we map the offsets from the initialization:
    // puVar1[0x11] = sub+0x20  => offset 0x44 (4*17 = 68)
    // puVar1[0x12] = sub+0x28  => 0x48
    // puVar1[0x13] = sub+0x30  => 0x4C
    // puVar1[0x14] = sub base  => 0x50
    // puVar1[0x15] = sub+0x10 => 0x54
    // Note: The exact layout may vary; we define convenient names.
    RectSubData* subData;       // +0x50 (pointer to sub object)
    void* subPtr10;             // +0x54 (sub+0x10)
    short* subPtr20;            // +0x44 (sub+0x20)
    short* subPtr28;            // +0x48 (sub+0x28)
    void* subPtr30;             // +0x4C (sub+0x30)
};

Rectangle* __thiscall createRect(Rectangle* this_, void* parent, short param2, short param3, short param4) {
    // Actually this function is not __thiscall; it allocates and returns pointer.
    // We'll implement as static factory.
    Rectangle* rect = (Rectangle*)allocate(0x78);
    if (!rect) return nullptr;

    rect->parent = parent;
    rect->field_4 = 0;
    rect->field_8 = 0;
    rect->field_C = 0;
    rect->field_10 = 0;
    rect->field_34 = 2; // likely rectangle type

    // Additional zeroing at various offsets (not all shown)
    // (the code zeros many more fields, we skip for brevity)

    RectSubData* sub = (RectSubData*)allocate(0x34);
    rect->subData = sub;
    rect->subPtr10 = (void*)((uint8_t*)sub + 0x10);
    rect->subPtr20 = (short*)((uint8_t*)sub + 0x20);
    rect->subPtr28 = (short*)((uint8_t*)sub + 0x28);
    rect->subPtr30 = (void*)((uint8_t*)sub + 0x30);

    // Initialize sub-struct fields
    sub->val28 = 0;
    sub->val20 = 0;
    sub->val2A = 0;
    sub->val22 = sub->val20 + param2; // = param2
    // Use a short from main object at offset 0x72 (which was zeroed)
    short baseShort = *(short*)((uint8_t*)rect + 0x72); // = 0
    sub->val2C = baseShort + param3; // = param3
    sub->val2E = sub->val2C - param4; // = param3 - param4
    sub->val24 = 0;
    sub->val26 = 0;

    // (some fields in main object may be set later)
    return rect;
}