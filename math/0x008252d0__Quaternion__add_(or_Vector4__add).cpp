// FUNC_NAME: Quaternion::add (or Vector4::add)
// Address: 0x008252d0
// Role: Adds two 4-component vectors (quaternions) and stores result in output.
// The class is expected to have a contiguous array of 4 floats (x, y, z, w).
void __thiscall Quaternion::add(const float *other, float *out) const
{
    // Load this's components
    float thisX = this[0]; // offset +0x0
    float thisY = this[1]; // offset +0x4
    float thisZ = this[2]; // offset +0x8
    float thisW = this[3]; // offset +0xC

    // Load other's components
    float otherX = other[0];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];

    // Sum and store to output
    out[0] = thisX + otherX;
    out[1] = thisY + otherY;
    out[2] = thisZ + otherZ;
    out[3] = thisW + otherW;
}