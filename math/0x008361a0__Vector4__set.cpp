// FUNC_NAME: Vector4::set
void __thiscall Vector4::set(void* thisPtr, const uint32_t* values)
{
    // Copy four consecutive 4-byte values into object fields at offsets +0x10, +0x14, +0x18, +0x1c
    // Probably representing a 4-component vector (e.g., RGBA color or XYZW position)
    *(uint32_t*)((uint8_t*)thisPtr + 0x10) = values[0];
    *(uint32_t*)((uint8_t*)thisPtr + 0x14) = values[1];
    *(uint32_t*)((uint8_t*)thisPtr + 0x18) = values[2];
    *(uint32_t*)((uint8_t*)thisPtr + 0x1c) = values[3];
}