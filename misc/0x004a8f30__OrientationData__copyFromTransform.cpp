// FUNC_NAME: OrientationData::copyFromTransform
// Function address: 0x004a8f30
// Role: Initialize a 20-byte orientation data structure (quaternion + scalar) from a larger transform object.
// If the source pointer is non-null, copies 5 dwords from specific offsets: +0x20..0x2c (4 values) and +0x18 (1 value).
// Otherwise, fills with debug sentinel values to aid in detecting uninitialized use.

void __thiscall OrientationData::copyFromTransform(void* source)
{
    // Debug sentinels (EA EARS engine debug build pattern)
    this->m_rotX = 0xbadbadba;  // +0x00: Quaternion X component
    this->m_rotY = 0xbeefbeef;  // +0x04: Quaternion Y component
    this->m_rotZ = 0xeac15a55;  // +0x08: Quaternion Z component
    this->m_rotW = 0x91100911;  // +0x0c: Quaternion W component
    this->m_scalar = 0;          // +0x10: Additional scalar value (e.g., angle or speed)

    if (source != 0)
    {
        // Copy from source object:
        // Source offsets: +0x20..0x2c are quaternion components
        //                +0x18 is the scalar
        this->m_rotX = *(int*)((char*)source + 0x20);
        this->m_rotY = *(int*)((char*)source + 0x24);
        this->m_rotZ = *(int*)((char*)source + 0x28);
        this->m_rotW = *(int*)((char*)source + 0x2c);
        this->m_scalar = *(int*)((char*)source + 0x18);
    }
}