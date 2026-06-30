// FUNC_NAME: initSplineLookupTable
void initSplineLookupTable(void)
{
    // Precomputes a cubic spline lookup table for 128 entries, 
    // mapping normalized parameter values to interpolated outputs.
    // The table is stored in a global array at 0x01162a10 with 0x18-byte entries.
    // Structure per entry:
    //   +0x00: float normalizedParam (input after scaling)
    //   +0x04: uint32 segmentIndex (0-3)
    //   +0x08: float (curveBase - normalizedParam)^3 * mult1
    //   +0x0C: float (normalizedParam^3 * mult2 - normalizedParam^3 * mult3 + constantOffset) * mult1
    //   +0x10: float (((mult2 - normalizedParam*mult2)*normalizedParam + mult2)*normalizedParam + curveBase) * mult1
    //   +0x14: float normalizedParam^3 * mult1

    float scale           = DAT_00e2af44;      // multiplier for parameter generation
    float curveBase       = DAT_00e2b1a4;      // base value used in spline
    float constantOffset  = DAT_00e2d99c;      // offset added in one formula
    float segmentLower[4] = { DAT_00e2e78c[0], DAT_00e2e78c[1], DAT_00e2e78c[2], DAT_00e2e78c[3] }; // lower bounds for each segment
    float segmentUpper[4] = { DAT_00e2e790[0], DAT_00e2e790[1], DAT_00e2e790[2], DAT_00e2e790[3] }; // upper bounds for each segment
    float mult1           = DAT_00e445f0;      // global multiplier 1
    float mult2           = DAT_00e445ac;      // global multiplier 2
    float mult3           = DAT_00e44634;      // global multiplier 3

    uint32 tableOffset = 0;  // byte offset into the global array at DAT_01162a10

    for (int32 i = 0; i < 128; i++)  // 128 entries: offset 0..0xBFF in steps of 0x18
    {
        float param = (float)i * scale;  // raw parameter

        // Find which segment the parameter falls into
        uint32 segIdx = 0;
        while (segIdx < 4)
        {
            if (param <= segmentUpper[segIdx])
                break;
            segIdx++;
        }

        // Normalize parameter within the segment [0..1]
        float norm = (param - segmentLower[segIdx]) / (segmentUpper[segIdx] - segmentLower[segIdx]);

        // Compute table values
        float valA = powf(curveBase - norm, 3) * mult1;          // stored at +0x08
        float valD = powf(norm, 3) * mult1;                        // stored at +0x14
        float valB = (norm*norm*norm * mult2 - norm*norm*norm * mult3 + constantOffset) * mult1; // stored at +0x0C
        float valC = (((mult2 - norm * mult2) * norm + mult2) * norm + curveBase) * mult1;        // stored at +0x10

        // Write to global table (note: addresses are hardcoded globals, we treat as array base)
        *(float*)((int)&DAT_01162a10 + tableOffset) = param;          // +0x00
        *(uint32*)((int)&DAT_01162a14 + tableOffset) = segIdx;       // +0x04
        *(float*)((int)&DAT_01162a18 + tableOffset) = valA;          // +0x08
        *(float*)((int)&DAT_01162a1c + tableOffset) = valB;          // +0x0C
        *(float*)((int)&DAT_01162a20 + tableOffset) = valC;          // +0x10
        *(float*)((int)&DAT_01162a24 + tableOffset) = valD;          // +0x14

        tableOffset += 0x18;  // advance to next entry
    }
}