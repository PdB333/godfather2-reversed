// FUNC_NAME: Vector4::scaleAdd
// Address: 0x0055a8d0
// Role: Performs a weighted addition: result = scale * this + other
// Class Vector4 likely holds 4 floats at offset 0 (x, y, z, w)

void __thiscall Vector4::scaleAdd(float *other, float scale, float *result)
{
    // Offsets: this[0] = x, this[1] = y, this[2] = z, this[3] = w
    result[0] = scale * this[0] + other[0];
    result[1] = scale * this[1] + other[1];
    result[2] = scale * this[2] + other[2];
    result[3] = scale * this[3] + other[3];
}