// FUNC_NAME: Vector4::sub

void __thiscall Vector4::sub(float *other, float *result) const
{
    // Subtract 4D vectors: result = this - other
    // this->v is stored as four consecutive floats at offset 0x00
    result[0] = this->v[0] - other[0];  // x
    result[1] = this->v[1] - other[1];  // y
    result[2] = this->v[2] - other[2];  // z
    result[3] = this->v[3] - other[3];  // w
}