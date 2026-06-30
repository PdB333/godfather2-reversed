// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(const float* other, float* out) const {
    // Subtract component-wise: out = *this - other
    out[0] = this->x - other[0];
    out[1] = this->y - other[1];
    out[2] = this->z - other[2];
    out[3] = this->w - other[3];
}