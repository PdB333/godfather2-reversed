// FUNC_NAME: Vector4::scaleTo
// Function address: 0x00836180
// Role: Scales a 4-component vector (x,y,z,w) by a scalar and writes the result to an output buffer.
// This is a member function of a math vector class, likely used in the EA EARS engine for 3D transformations.

#include <cstdint>

class Vector4 {
public:
    float v[4]; // Components: v[0]=x, v[1]=y, v[2]=z, v[3]=w

    // Scale this vector by 'scalar' and store the result in 'out'
    void scaleTo(float* out, float scalar) const {
        out[0] = v[0] * scalar;
        out[1] = v[1] * scalar;
        out[2] = v[2] * scalar;
        out[3] = v[3] * scalar;
    }
};