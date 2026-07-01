// FUNC_NAME: Vector4::scale
// Address: 0x00825e70
// Multiplies this 4D vector by a scalar and stores result in output array.

class Vector4 {
public:
    float x, y, z, w;

    // Scales this vector by scalar and writes to dest (4 floats).
    void __thiscall scale(float* dest, float scalar) const {
        dest[0] = scalar * x;
        dest[1] = scalar * y;
        dest[2] = scalar * z;
        dest[3] = scalar * w;
    }
};