// FUNC_NAME: adjustSizeFieldWithAlignment
// Function address: 0x00643e00
// Role: Clamps a size value (passed in EAX register), adds a header overhead (0xB),
//       aligns to an 8-byte boundary, enforces a minimum of 0x10,
//       and preserves the low bit (flag) of an existing field at offset +0x4.
// This is likely a helper for computing buffer sizes or alignment in network packet handling.

// Note: The calling convention is __fastcall with ECX (unused) and EDX (pointer to a struct with field at +0x4).
//       The new size is passed in EAX (not shown as formal parameter).

void __fastcall adjustSizeFieldWithAlignment(void* thisUnused, void* structPtr)
{
    // Offset +0x4 from the struct pointer is a uint field that holds a size with a low-bit flag.
    uint* field = (uint*)((char*)structPtr + 4);
    uint originalFlag = *field & 1;  // Preserve the low bit.

    // The value to set is provided in EAX. We'll use a placeholder here.
    uint value; // value comes from EAX (not a standard parameter)
    if (value > 0x50) {
        value = 0x50; // Clamp to maximum 80 (0x50)
    }

    uint alignedCandidate = value + 0xB; // Add header overhead (11 bytes)
    if (alignedCandidate > 0x10) {
        // Align down to multiple of 8, preserving low bit.
        *field = (alignedCandidate & 0xFFFFFFF8) | originalFlag;
    } else {
        // Enforce minimum of 0x10, preserving low bit.
        *field = originalFlag | 0x10;
    }
}