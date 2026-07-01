// FUNC_NAME: Vector4::add
// Function address: 0x00822e90
// Role: Adds two 4-element float vectors (Vector4). The 'this' pointer is the first operand, param_1 is the second, and param_2 is the output.

class Vector4 {
public:
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    void __thiscall add(const Vector4& other, Vector4& out) const {
        out.x = x + other.x;
        out.y = y + other.y;
        out.z = z + other.z;
        out.w = w + other.w;
    }
};