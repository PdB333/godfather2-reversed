// FUNC_NAME: Allocator::freeSmallBlock
// Function address: 0x00854380
// Reconstructed from Ghidra decompilation.
// EA EARS engine memory allocator: deallocates a small block of size 0x70 bytes.
// param_1 (this) points to an allocation record with fields:
//   +0x00: pBlock (pointer to the memory block being freed)
//   +0x04: ? (unknown)
//   +0x08: sizeIndexOrFlags (bitmask: top 2 bits used as flags, lower 30 bits as index)
// When the signed interpretation of sizeIndexOrFlags >= 0, the block is valid and freed.

void __fastcall Allocator::freeSmallBlock(Allocator* this)
{
    uint sizeIndexOrFlags;

    // Read the size/index field at offset 0x08
    sizeIndexOrFlags = this->sizeIndexOrFlags;  // param_1[2]

    // Check if block is valid: signed comparison (>= 0)
    if ((int)sizeIndexOrFlags >= 0) {
        // Get thread-local storage pointer (e.g., per-thread heap handle)
        TlsGetValue(DAT_01139810);

        // Call internal deallocation routine:
        // - First argument: pointer to the memory block (from +0x00)
        // - Second argument: index (masked to 30 bits) multiplied by block size (0x70)
        // - Third argument: constant 0x17 (23 decimal, likely a pool identifier)
        FUN_00aa26e0(
            this->pBlock,                          // *param_1
            (sizeIndexOrFlags & 0x3fffffff) * 0x70, // size = (index) * blockSize
            0x17                                   // pool ID or alignment
        );
    }
    return;
}