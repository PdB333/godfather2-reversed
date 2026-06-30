// FUNC_NAME: Vector4::add3D
// Function address: 0x005829d0
// 3D vector addition (x,y,z only) preserving the destination's w component

class Vector4 {
public:
    float x, y, z, w; // +0x00 x, +0x04 y, +0x08 z, +0x0C w

    // __thiscall: this in ECX, rhsA in EDX, rhsB on stack
    // Adds the first three components of rhsA and rhsB into this, keeps w unchanged
    void __thiscall add3D(const Vector4& rhsA, const Vector4& rhsB) {
        float originalW = this->w;

        this->x = rhsA.x + rhsB.x;
        this->y = rhsA.y + rhsB.y;
        this->z = rhsA.z + rhsB.z;

        this->w = originalW; // preserve original w
    }
};