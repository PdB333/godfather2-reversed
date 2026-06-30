// FUNC_NAME: SomeClass::init
// Function address: 0x006e8d90
// Identified role: Constructor/initializer for an object with vtable at offset 0 and a byte flag at +0xC

#include <cstdint>

class SomeClass {
public:
    void** vtable; // offset 0x00
    // ... other members ...
    uint8_t field_0xC; // offset 0x0C

    // Initializer, called with two parameters
    static SomeClass* init(SomeClass* obj, uint32_t param2, uint32_t param3);
};

// External function called during initialization (likely base constructor)
extern void FUN_00414970(uint32_t param2, uint32_t param3);

SomeClass* SomeClass::init(SomeClass* obj, uint32_t param2, uint32_t param3) {
    FUN_00414970(param2, param3);        // base initialization
    obj->vtable = (void**)0x00d5fc10;    // set vtable
    obj->field_0xC = 0;                  // clear byte at +0xC
    return obj;
}