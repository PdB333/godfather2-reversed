//FUNC_NAME: Vector4::add
struct Vector4 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    // Adds this vector to 'other' and stores result in 'result'
    void __thiscall add(const Vector4& other, Vector4& result) const {
        result.x = x + other.x;
        result.y = y + other.y;
        result.z = z + other.z;
        result.w = w + other.w;
    }
};