// FUNC_NAME: vector3Subtract
// Address: 0x00612ff0
// Role: Subtract two 3D vectors (first 3 components), preserving the 4th component (W) of the output.
// Note: Output pointer is passed in EAX (fastcall convention), but rewritten as standard function.
void __fastcall vector3Subtract(float *out, const float *a, const float *b)
{
    // Load source components
    float ay = a[1];
    float az = a[2];
    float aw = a[3];
    float by = b[1];
    float bz = b[2];
    float bw = b[3];
    // Save original output W (to preserve it)
    float savedW = out[3];

    // Compute difference of x,y,z components
    out[0] = a[0] - b[0];
    out[1] = ay - by;
    out[2] = az - bz;
    out[3] = aw - bw; // This is overwritten below
    out[3] = savedW;  // Restore original W, effectively only sub x,y,z
}