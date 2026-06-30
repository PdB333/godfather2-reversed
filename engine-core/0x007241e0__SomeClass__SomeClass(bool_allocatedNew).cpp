// FUNC_NAME: SomeClass::SomeClass(bool allocatedNew)

#include <cstdint>

// Base class constructor (address 0x00724010)
void __thiscall BaseClass::BaseClass();

// Function that records the object size for sized deletion (address 0x0043b960)
void __thiscall RegisterObjectSize(void* object, uint32_t size);

// Constructor at 0x007241e0
// param_2: flag, if low bit set, call RegisterObjectSize with class size 0x5c (92 bytes)
uint32_t __thiscall SomeClass::SomeClass(bool allocatedNew) {
    BaseClass::BaseClass();          // base class initialization
    if (allocatedNew) {
        RegisterObjectSize(this, 0x5c); // store size for custom sized delete
    }
    return this;                     // return this pointer
}