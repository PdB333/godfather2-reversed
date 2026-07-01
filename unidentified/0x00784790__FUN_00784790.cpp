// FUNC_NAME: SomeClass::computeBlendFactor
// Function address: 0x00784790
// Computes a blend/attenuation factor based on member floats and global thresholds.
// - Reads a base value at this+0x7c, subtracts a global baseline (DAT_01205228).
// - Defaults to a global constant (DAT_00d5ccf8, likely 1.0f).
// - If the result exceeds another global threshold (DAT_00d577a0),
//   computes a normalized ratio using (this+0x80 - result) / (this+0x80),
//   effectively fading the factor from 1 down to 0 as the result approaches (this+0x80).

// Known globals used (from analysis data):
// DAT_01205228: baseline offset
// DAT_00d5ccf8: default factor (likely 1.0f)
// _DAT_00d577a0: threshold to trigger fade

float __thiscall SomeClass::computeBlendFactor(void* thisPtr)
{
    float baseValue = *(float*)((char*)thisPtr + 0x7c);      // +0x7c: some current value (e.g., time, distance)
    float diff = baseValue - DAT_01205228;                    // Subtract global baseline

    float result = DAT_00d5ccf8;                              // Default factor (often 1.0)
    if (_DAT_00d577a0 < diff) {                               // If diff exceeds threshold, apply fade
        float maxValue = *(float*)((char*)thisPtr + 0x80);    // +0x80: upper limit for fade
        result = (maxValue - diff) / maxValue;                // Linear fade from 1.0 to 0.0 as diff approaches maxValue
    }
    return result;                                            // Converted to x87 10-byte float externally
}