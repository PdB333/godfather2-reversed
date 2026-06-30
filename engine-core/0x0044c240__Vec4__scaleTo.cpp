// FUNC_NAME: Vec4::scaleTo
// Address: 0x0044c240
// Role: Scales a 4-component vector (or quaternion) by a scalar and stores result in an output buffer.
// This is a member function where 'this' is the source vector and out is the destination.

struct Vec4 {
    float v[4]; // components: x, y, z, w

    // Scale this vector by scalar and write to out
    void scaleTo(float* out, float scalar) const {
        out[0] = scalar * v[0];
        out[1] = scalar * v[1];
        out[2] = scalar * v[2];
        out[3] = scalar * v[3];
    }
};