//FUNC_NAME: crossProduct3D
// Address: 0x0056c9f0
// Computes the cross product of two 3D vectors (stored as 4-component arrays) and stores the result in the output buffer.
// The fourth component (w) of the output is preserved (saved before overwriting and restored after zeroing).

void __fastcall crossProduct3D(float* out, const float* a, const float* b)
{
    float ax = a[0];
    float ay = a[1];
    float az = a[2];
    float aw = a[3];

    float bx = b[0];
    float by = b[1];
    float bz = b[2];
    float bw = b[3];

    // Save the original w component of the output vector
    float savedW = out[3];

    // Cross product: out = a × b
    out[0] = by * az - bz * ay;   // x = a.y*b.z - a.z*b.y
    out[1] = bz * ax - bx * az;   // y = a.z*b.x - a.x*b.z
    out[2] = bx * ay - by * ax;   // z = a.x*b.y - a.y*b.x

    // Temporarily zero the w component (bw*aw - bw*aw = 0)
    out[3] = bw * aw - bw * aw;

    // Restore the original w component
    out[3] = savedW;
}