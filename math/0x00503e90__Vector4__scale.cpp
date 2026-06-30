// FUNC_NAME: Vector4::scale
// Address: 0x00503e90
// Role: Scales a 4-component vector (this) by a scalar and writes result to output.
// Assumes Vector4 has members: x, y, z, w at offsets 0x00, 0x04, 0x08, 0x0C.

class Vector4 {
public:
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
    float w; // +0x0C

    // __thiscall: this in ECX, out in first stack param, scalar in second
    void __thiscall scale(float* out, float scalar) const {
        out[0] = scalar * x;
        out[1] = scalar * y;
        out[2] = scalar * z;
        out[3] = scalar * w;
    }
};