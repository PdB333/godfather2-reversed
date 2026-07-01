// FUNC_NAME: Vec4::subtract at address 0x008252f0

// Represents a 4-component floating-point vector.
// Offsets: +0x00 x, +0x04 y, +0x08 z, +0x0C w
struct Vec4 {
    float x;
    float y;
    float z;
    float w;

    // Subtract another Vec4 and store result in output.
    // void __thiscall subtract(const Vec4* other, Vec4* out) const
    void subtract(const Vec4& other, Vec4& out) const {
        out.x = x - other.x;
        out.y = y - other.y;
        out.z = z - other.z;
        out.w = w - other.w;
    }
};