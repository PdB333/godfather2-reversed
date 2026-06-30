// FUNC_NAME: crossProduct3D
// Address: 0x0058a7b0 - Computes cross product of two 4-component vectors (3D cross on xyz, w preserved).
// Output pointer is passed in EAX (fastcall: ECX unused, EDX = a, stack = b).
void __fastcall crossProduct3D(int dummy, float *vecA, float *vecB)
{
    float ax = vecA[0];
    float ay = vecA[1];
    float az = vecA[2];
    float aw = vecA[3];
    float bx = vecB[0];
    float by = vecB[1];
    float bz = vecB[2];
    float bw = vecB[3];
    
    // Output pointer assumed to be in EAX (register, not a parameter).
    // For reconstruction, we treat it as a local pointer that would be assigned externally.
    float *out; // The actual output address is expected to be in EAX.
    
    // Cross product of 3D vectors: out.xyz = vecA.xyz × vecB.xyz
    out[0] = by * az - bz * ay; // a.y * b.z - a.z * b.y
    out[1] = bz * ax - bx * az; // a.z * b.x - a.x * b.z
    out[2] = bx * ay - by * ax; // a.x * b.y - a.y * b.x
    // out.w preserved (saved before overwrite)
    out[3] = aw; // original w of output (from EAX[3] before modification)
}