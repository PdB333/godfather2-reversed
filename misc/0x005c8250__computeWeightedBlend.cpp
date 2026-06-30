// FUNC_NAME: computeWeightedBlend
// Address: 0x005c8250
// Role: Computes a weighted blend of 8 table entries, scaling 4 of them by a constant factor.
// Used in bone blending or skinning calculations (likely part of EARS animation system).
void __cdecl computeWeightedBlend(float *outResult)
{
    // Global constants
    extern float *gTable;      // PTR_DAT_00f17644 - float lookup table (256 entries)
    extern float gScaleFactor; // DAT_00e2eb58 - scaling factor (e.g., 1/256 or bone weight)

    // in_EAX holds 8 consecutive byte indices into the table (index array)
    // in_EAX is passed in EAX by convention; here we assume a local pointer for clarity.
    // The actual calling code passes a char* in EAX.
    char *indices; // assumed to be set from EAX before call

    // Compute scaled contributions
    float scale0 = gScaleFactor * gTable[indices[2]];
    float scale1 = gScaleFactor * gTable[indices[4]];
    float scale2 = gScaleFactor * gTable[indices[6]];
    float base0 = gTable[indices[3]];
    float base1 = gTable[indices[5]];
    float base2 = gTable[indices[7]];

    // First component: index0 * scale + index1 (no scale)
    outResult[0] = gScaleFactor * gTable[indices[0]] + gTable[indices[1]];

    // Remaining three components: scaled contributions + bases
    outResult[1] = scale0 + base0;
    outResult[2] = scale1 + base1;
    outResult[3] = scale2 + base2;
}