// FUNC_NAME: Vec3AddPreserveW (or VectorMath::addWithWPreserve)
// Address: 0x004cd330
// Description: Adds two 4-element vectors (float[4]) but preserves the 4th component of the destination.
// Parameters are passed via fastcall: ECX unused, EDX = srcA, stack = srcB. EAX points to destination.

void __fastcall Vec3AddPreserveW(void* unusedThis, float* srcA, float* srcB)
{
    // Load source components (index 1,2,3), but note: param_2 is srcA, param_3 is srcB
    float a1 = srcA[1];
    float a2 = srcA[2];
    float a3 = srcA[3];
    float b1 = srcB[1];
    float b2 = srcB[2];
    float b3 = srcB[3];
    // EAX holds destination pointer (hidden register parameter)
    float* dest = (float*)in_EAX; // in_EAX is the EAX register at call time
    float destW = dest[3]; // Preserve original 4th component
    dest[0] = srcA[0] + srcB[0];
    dest[1] = a1 + b1;
    dest[2] = a2 + b2;
    dest[3] = a3 + b3;
    dest[3] = destW; // Overwrite with saved original (no change to w)
}
// Note: The actual prototype for fastcall expects ECX (here unused) and EDX as first two parameters.
// The stack parameter (srcB) is passed third. The EAX register is treated as an implicit destination pointer.
// This is likely a compiler intrinsic or hand-written assembly for EA's math library.