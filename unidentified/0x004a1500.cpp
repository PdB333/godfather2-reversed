// FUN_004a1500: blend3ComponentsWithWeights

// Blends the first three components of two 4-element vectors into a destination vector,
// preserving the fourth component (w) of the destination.
// dest = weightA * srcA + weightB * srcB  (only x,y,z updated)
// Note: Parameter order as per __fastcall: dest in ECX, srcA in EDX, then weightB, srcB, weightA on stack.
void __fastcall blend3ComponentsWithWeights(float* dest, const float* srcA, float weightB, const float* srcB, float weightA)
{
    // Preserve original w component
    float w = dest[3];

    // Blend x, y, z
    dest[0] = weightA * srcA[0] + weightB * srcB[0];
    dest[1] = weightA * srcA[1] + weightB * srcB[1];
    dest[2] = weightA * srcA[2] + weightB * srcB[2];

    // Restore w (unchanged)
    dest[3] = w;
}