// FUNC_NAME: crossProduct4D
void __fastcall crossProduct4D(float *out, float *a, float *b)
{
    // Compute cross product of 3D components (x,y,z) of two 4D vectors,
    // preserve the w component of the output (in place).
    // out is passed in EAX, a in EDX, b on stack (param_3).
    // a and b are 4-float arrays: [x,y,z,w].
    // out is also 4-float array.

    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3];
    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3];

    float savedW = out[3]; // preserve original w

    out[0] = by * az - bz * ay;   // cross.x = a.y*b.z - a.z*b.y
    out[1] = bz * ax - bx * az;   // cross.y = a.z*b.x - a.x*b.z
    out[2] = bx * ay - by * ax;   // cross.z = a.x*b.y - a.y*b.x
    out[3] = bw * aw - bw * aw;   // = 0, then restored below
    out[3] = savedW;               // restore original w
}