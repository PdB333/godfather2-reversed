// FUNC_NAME: Vector4::subtractTo
// Address: 0x00582a20
// Role: Vector4 member function computing this - other and storing result in out.

struct Vector4 {
    float x, y, z, w; // +0x00: x, +0x04: y, +0x08: z, +0x0C: w

    // Stores the difference (this - other) into 'out'.
    // Equivalent to out = *this - other;
    void __thiscall subtractTo(const Vector4& other, Vector4& out) const {
        out.x = x - other.x;
        out.y = y - other.y;
        out.z = z - other.z;
        out.w = w - other.w;
    }
};