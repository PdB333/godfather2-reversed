// FUNC_NAME: SomeGameObject::constructor
// Address: 0x00503e00
// Role: Constructor with optional initialization flag. Calls base constructor (FUN_00503af0) and conditionally calls additional setup (FUN_009c8eb0) if the low bit of flags is set.
// Typical EA EARS pattern: constructors take a byte flag for heap/stack allocation; bit 0 triggers extra registration or allocation.

#include <cstdint>

// Forward declarations of callees (addresses in comments)
void baseConstructor();                // FUN_00503af0 – likely base class constructor/init
void extraInit(SomeGameObject* obj);   // FUN_009c8eb0 – conditional post‑construction step

SomeGameObject* SomeGameObject::constructor(uint8_t flags) {
    // Call base class constructor/initializer
    baseConstructor(); // FUN_00503af0

    // If the low bit of flags is set, perform additional initialization
    if (flags & 1) {
        extraInit(this); // FUN_009c8eb0 – e.g., registration or heap‑allocation setup
    }

    return this;
}