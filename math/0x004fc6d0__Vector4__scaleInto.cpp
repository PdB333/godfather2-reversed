// FUNC_NAME: Vector4::scaleInto
// Address: 0x004fc6d0
// Role: Scale a 4D vector (quaternion or homogeneous vector) by a scalar, storing result to an output pointer.
// Structure offsets: +0x00 x, +0x04 y, +0x08 z, +0x0C w
void __thiscall Vector4::scaleInto(float* out, float scalar) const
{
    // Multiply each component by the scalar and store at the destination
    // Note: out can equal 'this' safely (in-place scaling)
    out[0] = this->x * scalar;  // +0x00
    out[1] = this->y * scalar;  // +0x04
    out[2] = this->z * scalar;  // +0x08
    out[3] = this->w * scalar;  // +0x0C
}