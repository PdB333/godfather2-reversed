// FUNC_NAME: Vector4::scale
// Address: 0x00822e70
// Role: Scales a 4-component vector (x,y,z,w) by a scalar and stores result in output.
// Uses __thiscall: `this` is the source vector, param_1 is output, param_2 is scalar.

void __thiscall Vector4::scale(float *out, float scalar) const
{
    // Load components from this pointer
    float x = x; // Assume Vector4 has members x, y, z, w
    float y = y;
    float z = z;
    float w = w;

    // Multiply each component by scalar and store to output
    out[0] = scalar * x;
    out[1] = scalar * y;
    out[2] = scalar * z;
    out[3] = scalar * w;
}