// FUNC_NAME: EARSObject::loadFromProvider
// Function address: 0x004151a0
// Role: Copies 16 dwords (64 bytes) from a provider into the object's data array.
// Assumes object has a vtable pointer at +0x0, and a member pointer at +0x0C (mDataProvider).
// The provider's virtual function at vtable offset 0x60 (index 24) returns a pointer to 16 dwords.

#include <cstring>

void EARSObject::loadFromProvider()
{
    // Get the data provider from this+0x0C
    // The provider is a pointer to an object with a vtable; call virtual function at vtable+0x60
    uint32_t* source = (*(uint32_t* (*)())(**(int**)(this + 0x0C) + 0x60))(); // +0x0C: mDataProvider

    // Copy 16 dwords (64 bytes) from source into the object's beginning (this+0x00)
    uint32_t* dest = reinterpret_cast<uint32_t*>(this); // +0x00: mData array (16 ints)
    for (int i = 0; i < 16; i += 4)
    {
        dest[i+0] = source[i+0];
        dest[i+1] = source[i+1];
        dest[i+2] = source[i+2];
        dest[i+3] = source[i+3];
    }
}