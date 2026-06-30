// FUNC_NAME: Vector4::scaledAdd

struct Vector4 {
    float x, y, z, w;

    // Adds the scaled version of this vector to the 'other' vector.
    // result = other + factor * this
    void scaledAdd(const Vector4& other, float factor, Vector4& out) const {
        out.x = this->x * factor + other.x; // +0x00
        out.y = this->y * factor + other.y; // +0x04
        out.z = this->z * factor + other.z; // +0x08
        out.w = this->w * factor + other.w; // +0x0C
    }
};