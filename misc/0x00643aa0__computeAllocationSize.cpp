// FUNC_NAME: computeAllocationSize
// Function address: 0x00643aa0
// Computes aligned allocation size with minimum 16 bytes and 8-byte alignment.
// Takes requested size in EAX (__fastcall style), adds 11 bytes overhead, rounds up to multiple of 8,
// and enforces a minimum of 16 bytes.

uint __fastcall computeAllocationSize(uint size)
{
    // Add 11 bytes for internal header/overhead
    uint total = size + 0xb;

    // If total exceeds 16, align to 8-byte boundary (mask lower 3 bits)
    if (0x10 < total) {
        return total & 0xfffffff8;
    }

    // Minimum allocation size is 16 bytes
    return 0x10;
}