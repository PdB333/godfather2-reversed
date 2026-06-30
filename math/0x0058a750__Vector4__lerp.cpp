// FUNC_NAME: Vector4::lerp
// Function address: 0x0058a750
// Role: 4-component vector linear interpolation: out = t * this + from
// Operates on float arrays of length 4 (e.g., Vector4 or quaternion).

void __thiscall Vector4::lerp(float *from, float t, float *out)
{
    // Components of the 'this' vector
    float thisX = this[0];
    float thisY = this[1];
    float thisZ = this[2];
    float thisW = this[3];

    // Components of the 'from' vector
    float fromX = from[0];
    float fromY = from[1];
    float fromZ = from[2];
    float fromW = from[3];

    // Compute output: out = t * this + from
    out[0] = t * thisX + fromX;
    out[1] = t * thisY + fromY;
    out[2] = t * thisZ + fromZ;
    out[3] = t * thisW + fromW;
}