// FUNC_NAME: Vector4::crossProduct
// Function address: 0x004eb280
// Computes cross product of two 4D vectors (ignoring W component) and stores result in output.
void __thiscall Vector4::crossProduct(const Vector4& other, Vector4& out) const {
    float x1 = this->x;   // +0x00
    float y1 = this->y;   // +0x04
    float z1 = this->z;   // +0x08
    float w1 = this->w;   // +0x0C

    float x2 = other.x;   // +0x00
    float y2 = other.y;   // +0x04
    float z2 = other.z;   // +0x08
    float w2 = other.w;   // +0x0C

    out.x = y1 * z2 - z1 * y2;  // +0x00
    out.y = z1 * x2 - x1 * z2;  // +0x04
    out.z = x1 * y2 - y1 * x2;  // +0x08
    out.w = w1 * w2 - w1 * w2;  // +0x0C, always zero
}