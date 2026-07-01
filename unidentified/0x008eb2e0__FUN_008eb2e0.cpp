// FUNC_NAME: UnknownClass::UnknownClass

#include <cstdint>

// Function at 0x008eb2e0: Constructor or initializer that calls common initialization routine and returns this pointer.
void* __fastcall UnknownClass::UnknownClass(void* this)
{
    // Calls base class constructor or common initialization (0x008ea6a0)
    ::FUN_008ea6a0();
    return this;
}