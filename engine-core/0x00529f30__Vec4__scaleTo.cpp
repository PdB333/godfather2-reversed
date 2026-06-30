// FUNC_NAME: Vec4::scaleTo
// Address: 0x00529f30
// Multiplies this Vec4 by a scalar and stores result in output vector.

class Vec4 {
public:
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    void scaleTo(Vec4 &out, float scalar) const {
        out.x = scalar * x;
        out.y = scalar * y;
        out.z = scalar * z;
        out.w = scalar * w;
    }
};