// FUN_00471590: AuthHashGenerator::computeResponse

class AuthHashGenerator {
public:
    void __thiscall computeResponse(uint32_t* outHash, uint32_t inSize, bool doTransform);
};

// This function appears to generate a 64-byte (16 dword) authentication hash or key.
// The source of the local buffer is unclear from the decompiled code; it may be
// filled by the prior vtable call or by a global random generator.
void __thiscall AuthHashGenerator::computeResponse(uint32_t* outHash, uint32_t inSize, bool doTransform) {
    // Call virtual method at vtable offset 0x8c (likely a hash initialization)
    (this->vtable[0x8c / 4])(outHash, inSize, 1);

    // Global entropy/seed update (no arguments - possibly modifies static state)
    FUN_00417560();

    // Temporary buffer on stack (0x10 dwords = 64 bytes)
    uint32_t localBuffer[16];

    // Copy local buffer to output (overwriting any data from vtable call)
    for (int i = 0; i < 16; i++) {
        outHash[i] = localBuffer[i];
    }

    // If flag set, apply additional transformation (e.g., XOR, byte swap)
    if (doTransform) {
        FUN_0043a2a0(outHash, outHash);
    }
}