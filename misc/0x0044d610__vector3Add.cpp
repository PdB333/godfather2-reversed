// FUNC_NAME: vector3Add
// Function address: 0x0044d610
// Role: Adds two 3D vectors (stored as 4-float arrays), preserving the destination's fourth component (w).
// The function takes three float pointers: 'a' and 'b' are input vectors, 'out' is the output.
// The x,y,z components are added; the w component of 'out' remains unchanged.

void vector3Add(const float* a, const float* b, float* out) {
    float aY = a[1];
    float aZ = a[2];
    float aW = a[3];
    float bY = b[1];
    float bZ = b[2];
    float bW = b[3];
    float outWOriginal = out[3]; // preserve original output w

    out[0] = a[0] + b[0];       // x component
    out[1] = aY + bY;           // y component
    out[2] = aZ + bZ;           // z component
    out[3] = aW + bW;           // temporarily set w sum (overwritten)
    out[3] = outWOriginal;      // restore original w
}