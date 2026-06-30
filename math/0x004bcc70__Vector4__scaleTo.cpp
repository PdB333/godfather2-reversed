// FUNC_NAME: Vector4::scaleTo
// Function address: 0x004bcc70
// Role: Multiplies each component of a 4‑component vector (this) by a scalar and stores the result in a destination vector.
// The source is read via the implicit this pointer (passed in EAX) and the destination is the first explicit parameter.
// Field offsets: v[0] at +0x00, v[1] at +0x04, v[2] at +0x08, v[3] at +0x0C.

class Vector4 {
public:
    float v[4]; // x, y, z, w (or as interpreted by the game)
};

void __thiscall Vector4::scaleTo(Vector4* out, float s) const {
    out->v[0] = this->v[0] * s;
    out->v[1] = this->v[1] * s;
    out->v[2] = this->v[2] * s;
    out->v[3] = this->v[3] * s;
}