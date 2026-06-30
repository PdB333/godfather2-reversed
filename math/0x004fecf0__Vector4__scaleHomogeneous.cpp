// FUNC_NAME: Vector4::scaleHomogeneous
void __thiscall Vector4::scaleHomogeneous(float *this, const float *vec, float scalar)
{
    // Scale the first three components (x,y,z) by scalar, but preserve the fourth component (w) unchanged.
    this[0] = vec[0] * scalar; // +0x00: x
    this[1] = vec[1] * scalar; // +0x04: y
    this[2] = vec[2] * scalar; // +0x08: z
    this[3] = vec[3];          // +0x0c: w (homogeneous coordinate, kept intact)
}