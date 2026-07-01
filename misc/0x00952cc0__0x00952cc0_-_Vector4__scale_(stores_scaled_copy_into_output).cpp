// FUNC_NAME: 0x00952cc0 - Vector4::scale (stores scaled copy into output)
// Role: Scales a 4-element vector by a scalar and writes result to an output vector.

class Vector4 {
public:
    float x, y, z, w;

    // +0x00: x
    // +0x04: y
    // +0x08: z
    // +0x0C: w

    // __thiscall: this = in_EAX (source vector)
    // Returns: none
    // Writes scaled copy to 'out'
    void __thiscall scale(float *out, float scalar) const {
        out[0] = scalar * x;
        out[1] = scalar * y;
        out[2] = scalar * z;
        out[3] = scalar * w;
    }
};