// FUNC_NAME: Vector4::scaleAdd
// Function address: 0x00514440
// Computes: out[i] = scalar * this->data[i] + other[i] for i=0..3
// Used for 4-component vector (e.g., quaternion or homogeneous coordinate) linear combination

void __thiscall Vector4::scaleAdd(const float* other, float scalar, float* out) const
{
    // Accessing this's components (stored as float[4])
    float thisX = this->x;   // +0x00
    float thisY = this->y;   // +0x04
    float thisZ = this->z;   // +0x08
    float thisW = this->w;   // +0x0C

    float otherX = other[0]; // +0x00
    float otherY = other[1]; // +0x04
    float otherZ = other[2]; // +0x08
    float otherW = other[3]; // +0x0C

    out[0] = scalar * thisX + otherX;
    out[1] = scalar * thisY + otherY;
    out[2] = scalar * thisZ + otherZ;
    out[3] = scalar * thisW + otherW;
}