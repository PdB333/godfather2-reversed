// FUNC_NAME: Quaternion::addWeighted
// Address: 0x0055a8d0
// This function computes: result = this * weight + other
// Used for weighted blending of quaternion components (linear combination)
// Struct layout: float[4] starting at +0x00 (x, y, z, w)

void __thiscall Quaternion::addWeighted(const float* other, float weight, float* result) const
{
    // Read this quaternion components
    float x = this->x;   // +0x00
    float y = this->y;   // +0x04
    float z = this->z;   // +0x08
    float w = this->w;   // +0x0C

    // Read other quaternion components
    float otherX = other[0]; // +0x00
    float otherY = other[1]; // +0x04
    float otherZ = other[2]; // +0x08
    float otherW = other[3]; // +0x0C

    // Compute weighted sum
    result[0] = weight * x + otherX;   // output.x
    result[1] = weight * y + otherY;   // output.y
    result[2] = weight * z + otherZ;   // output.z
    result[3] = weight * w + otherW;   // output.w
}