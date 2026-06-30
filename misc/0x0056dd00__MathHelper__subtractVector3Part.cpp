// FUNC_NAME: MathHelper::subtractVector3Part
// Address: 0x0056dd00
// Purpose: Subtracts two 3-component vectors (x,y,z) element-wise, preserving the fourth component (w) of the destination.
// Parameters are assumed to be (in_EAX: dest, param_2: srcA, param_3: srcB) based on decompilation.
void __fastcall subtractVector3Part(const float *srcA, const float *srcB, float *dest)
{
    // Save original w component of destination
    float wOriginal = dest[3];
    
    // Subtract x, y, z components
    dest[0] = srcA[0] - srcB[0];
    dest[1] = srcA[1] - srcB[1];
    dest[2] = srcA[2] - srcB[2];
    
    // Restore preserved w component
    dest[3] = wOriginal;
}