// FUNC_NAME: Vector4::scaleTo
// Address: 0x0052b700
// This function multiplies a 4-component vector stored in the object by a scalar and writes the result to an output array.
// It is a member function of a Vector4 class (likely from EARS math library).

void __thiscall Vector4::scaleTo(float *out, float scalar)
{
    // this pointer (in_EAX) points to a float[4] member
    out[0] = scalar * this[0];  // +0x00
    out[1] = scalar * this[1];  // +0x04
    out[2] = scalar * this[2];  // +0x08
    out[3] = scalar * this[3];  // +0x0C
}