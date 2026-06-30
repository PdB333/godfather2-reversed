// FUNC_NAME: Vector4::addScaledVector
// Function address: 0x006dfc90
// Role: Performs addition of this vector scaled by a factor to another vector, storing result in output.
// Equivalent to: out = (this * scale) + other
// This is a member function of a 4-component float vector likely used in EA EARS engine math.

struct Vector4 {
    float x, y, z, w; // +0x00, +0x04, +0x08, +0x0C
};

void __thiscall Vector4::addScaledVector(float scale, const Vector4& other, Vector4& out) const
{
    // Load this vector components
    float thisX = this->x;
    float thisY = this->y;
    float thisZ = this->z;
    float thisW = this->w;

    // Load other vector components
    float otherX = other.x;
    float otherY = other.y;
    float otherZ = other.z;
    float otherW = other.w;

    // Compute and store result: out = (this * scale) + other
    out.x = scale * thisX + otherX;
    out.y = scale * thisY + otherY;
    out.z = scale * thisZ + otherZ;
    out.w = scale * thisW + otherW;
}