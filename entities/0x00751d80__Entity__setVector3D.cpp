// FUNC_NAME: Entity::setVector3D
// Address: 0x00751d80
// Stores three 8-byte values (likely double-precision floats or pointers) at offsets +0x90, +0x98, +0xA0.

void __thiscall Entity::setVector3D(void* thisPtr, double val1, double val2, double val3)
{
    // Offsets into the Entity structure
    *(double*)((uint8_t*)thisPtr + 0x90) = val1; // +0x90: first component (e.g., x)
    *(double*)((uint8_t*)thisPtr + 0x98) = val2; // +0x98: second component (y)
    *(double*)((uint8_t*)thisPtr + 0xA0) = val3; // +0xA0: third component (z)
}