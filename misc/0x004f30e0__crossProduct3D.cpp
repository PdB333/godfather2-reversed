// FUNC_NAME: crossProduct3D
void __fastcall crossProduct3D(float* out, const float* a, const float* b)
{
    // Load components of input vectors (assuming 4-component floats, but only x,y,z used)
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3]; // w component preserved

    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3];

    // Save original w component of output vector
    float oldW = out[3];

    // Compute cross product of (ax,ay,az) and (bx,by,bz)
    out[0] = ay * bz - az * by; // x component
    out[1] = az * bx - ax * bz; // y component
    out[2] = ax * by - ay * bx; // z component

    // Preserve the original w component (fourth element unaffected by cross product)
    out[3] = oldW;
}