// FUNC_NAME: UnknownClass::findByteWithAllBitsSet
// Address: 0x00497110
// Role: Search a 64-bit bitmask for the first byte (8-bit group) where all bits are set.
// Returns the byte index (0..3) if found, or -1 if none in the low 32 bits.
// Note: Only checks the low 32 bits (4 bytes) because the loop shifts up to 24 bits.
// The __allshl() helper shifts a 64-bit value left (low:high pair) by a count.

int __thiscall findByteWithAllBitsSet(void* thisPtr)
{
    uint lowMask;
    uint highMask;
    uint* bitMaskPtr;
    uint shift;
    int byteIndex;
    unsigned long long shiftedMask1;
    unsigned long long shiftedMask2;

    // The object stores a 64‑bit mask in two consecutive 32‑bit words (+0x0 and +0x4)
    bitMaskPtr = (uint*)thisPtr;
    lowMask = bitMaskPtr[0];
    highMask = bitMaskPtr[1];

    shift = 0;
    byteIndex = 0;

    do {
        // Construct mask for current byte position:
        // Mask = (0xFF << shift)  (only low part matters for shift < 32)
        // In the original code, two calls to __allshl produce the 64‑bit mask.
        // The first call shifts some base value (likely 0xFF) left by 'shift'.
        shiftedMask1 = __allshl(0xFF, 0, shift);    // low part = 0xFF << shift, high part = (0xFF << (shift-32)) if shift >=32
        // The second call might shift a similar mask? Actually the two calls are identical in pattern.
        // In the decompiled logic, the second result is compared with the masked original value.
        // For simplicity, we assume shiftedMask1 contains the required mask.
        shiftedMask2 = __allshl(0xFF, 0, shift);

        // Check if the mask matches exactly the corresponding bits in the stored mask.
        // That is, if (mask & storedMask) == mask (all bits in the byte are set).
        unsigned long long storedMask = ((unsigned long long)highMask << 32) | lowMask;
        if (shiftedMask2 == (storedMask & shiftedMask1)) {
            return byteIndex;
        }

        byteIndex++;
        shift += 8;
    } while (shift < 32);   // only checks first 4 bytes (0..24 bits)

    return -1;
}