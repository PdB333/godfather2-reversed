// FUNC_NAME: Vector4::scaleAdd
void __thiscall Vector4::scaleAdd(const float* other, float scalar, float* result) const
{
    // this points to 4 floats: x, y, z, w
    // other points to another 4 floats
    // result points to output 4 floats
    // Performs: result[i] = scalar * this[i] + other[i] for i=0..3
    result[0] = scalar * this[0] + other[0];
    result[1] = scalar * this[1] + other[1];
    result[2] = scalar * this[2] + other[2];
    result[3] = scalar * this[3] + other[3];
}