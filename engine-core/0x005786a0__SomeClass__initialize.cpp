// FUNC_NAME: SomeClass::initialize
// Address: 0x005786a0
// Calls a static function to retrieve a value and passes it to a member setter.

#include <cstdint>

// Forward declarations for callees
uint32_t __cdecl getSingletonValue(void); // FUN_00579870
void __thiscall SomeClass::setValue(uint32_t value); // FUN_00579450

void __thiscall SomeClass::initialize(void) {
    uint32_t value = getSingletonValue();
    this->setValue(value);
}