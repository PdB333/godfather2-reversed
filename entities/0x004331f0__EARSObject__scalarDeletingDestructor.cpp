// FUNC_NAME: EARSObject::scalarDeletingDestructor
// Function address: 0x004331f0
// Role: Scalar deleting destructor wrapper. Calls the actual destructor at 0x00433210,
// then conditionally calls operator delete at 0x009c8eb0 if the low bit of the flag is set.

#include <cstdint>

uint32_t __thiscall EARSObject::scalarDeletingDestructor(EARSObject* this, uint8_t flags)
{
    // Call the class destructor (base + member destruction)
    this->destructor(); // Address: 0x00433210

    // If the delete flag (low bit) is set, free the memory via operator delete
    if ((flags & 1) != 0)
    {
        // Operator delete for this object
        operatorDelete(this); // Address: 0x009c8eb0
    }

    return reinterpret_cast<uint32_t>(this);
}