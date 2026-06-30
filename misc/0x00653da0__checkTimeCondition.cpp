// FUNC_NAME: checkTimeCondition
// Function address: 0x00653da0
// This function computes a state based on elapsed time (delta between two ints at +0x94 and +0x98).
// It returns either a masked value (low byte forced to 0 or 1) or a boolean depending on flags and threshold.
// Likely part of a timer or distance check in EARS object.

int __fastcall checkTimeCondition(int this)
{
    float fVar1;
    unsigned int delta;
    unsigned int uVar3; // 24-bit value (uint3)

    delta = *(int *)(this + 0x98) - *(int *)(this + 0x94); // end time - start time?
    uVar3 = (unsigned int)(delta >> 8); // high 24 bits of delta

    if (delta > 0x1d) {
        // For large delta, return delta with low byte forced to 1
        return (delta & 0xFFFFFF00) | 1;
    }

    // Check flags at +0xb8, bits 2 and 3 (0x0C)
    if ((*(byte *)(this + 0xb8) & 0x0C) != 0) {
        // Convert delta to float (handling unsigned overflow)
        fVar1 = (float)(int)delta;
        if ((int)delta < 0) {
            fVar1 = fVar1 + 4294967296.0f; // DAT_00e44578 = 2^32 as float
        }
        // Compare against threshold at +0x1b8
        if (*(float *)(this + 0x1b8) <= fVar1) {
            return 1;
        }
        return 0;
    }

    // Otherwise return delta with low byte zeroed
    return (unsigned int)uVar3 << 8; // equivalent to delta & 0xFFFFFF00
}