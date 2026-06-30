// FUNC_NAME: EARSObject::getExtraDataPointer
// Address: 0x0044d960
// Role: Returns a pointer at offset +0x90 if the bit 3 (0x08) of the byte at +0x94 is set.
//        Otherwise returns nullptr. This is a safe getter for optional data.
// Offsets:
//   +0x94: byte containing flags (bit 3 = data present)
//   +0x90: pointer to associated extra data (4 bytes)

void* __thiscall EARSObject::getExtraDataPointer() {
    // Check if the "data present" flag (bit 3) is set in the flags byte at +0x94
    if ((*(uint8_t*)((uintptr_t)this + 0x94) & 0x08) != 0) {
        // Return the pointer stored at +0x90
        return *(void**)((uintptr_t)this + 0x90);
    }
    return nullptr;
}