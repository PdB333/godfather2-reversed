// FUNC_NAME: Vector4::negateTo
// Address: 0x0056c940
// Copies the negation of this vector (4 floats) into the output vector.
// Equivalent to: out.x = -x, out.y = -y, out.z = -z, out.w = -w

class Vector4 {
public:
    float v[4]; // offsets: +0x0, +0x4, +0x8, +0xC

    void __thiscall negateTo(Vector4 &out) const {
        out.v[0] = -v[0];
        out.v[1] = -v[1];
        out.v[2] = -v[2];
        out.v[3] = -v[3];
    }
};