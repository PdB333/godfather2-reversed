// FUNC_NAME: Vector4::scaleXYZ
// Address: 0x004f1a80
// Scales the x, y, z components of this vector from a source vector and a scalar, preserving the w component.
void __thiscall Vector4::scaleXYZ(const Vector4& source, float scalar)
{
    // Store original w of this vector (destination)
    float originalW = this->w;

    // Scale x, y, z from source
    this->x = scalar * source.x;
    this->y = scalar * source.y;
    this->z = scalar * source.z;

    // Restore w unchanged
    this->w = originalW;
}