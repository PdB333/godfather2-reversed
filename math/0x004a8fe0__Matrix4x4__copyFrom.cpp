// FUNC_NAME: Matrix4x4::copyFrom
void __thiscall Matrix4x4::copyFrom(const uint32_t* source) {
    // Copy 16 dwords (64 bytes) from source to this object.
    // Likely copies a 4x4 float matrix (16 floats).
    uint32_t* dest = reinterpret_cast<uint32_t*>(this);
    int remaining = 0x10;
    while (remaining != 0) {
        *dest = *source;
        ++source;
        ++dest;
        --remaining;
    }
}