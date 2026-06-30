// FUNC_NAME: Vec4::add
// Function address: 0x0056c920
// Adds two 4-component vectors (this + other) and stores result in out.

struct Vec4 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    void __thiscall add(const Vec4& other, Vec4& out) const {
        out.x = x + other.x;
        out.y = y + other.y;
        out.z = z + other.z;
        out.w = w + other.w;
    }
};