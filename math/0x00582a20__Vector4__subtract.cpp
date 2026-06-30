// FUNC_NAME: Vector4::subtract
// Address: 0x00582a20
// Subtracts another vector from this vector and stores result in output.
void __thiscall Vector4::subtract(const float *other, float *out) {
    out[0] = this[0] - other[0];
    out[1] = this[1] - other[1];
    out[2] = this[2] - other[2];
    out[3] = this[3] - other[3];
}