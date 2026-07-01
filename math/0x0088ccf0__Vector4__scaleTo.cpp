// FUNC_NAME: Vector4::scaleTo
// Function at 0x0088ccf0: Scalar multiplication of a 4-component vector, storing result to a provided output.
// Known pattern: multiplies each component of 'this' by scalar and writes to output pointer.
void __thiscall Vector4::scaleTo(float *out, float scalar) const
{
    // Perform scalar multiplication on each component
    out[0] = scalar * this->x;  // this[0] = x
    out[1] = scalar * this->y;  // this[1] = y
    out[2] = scalar * this->z;  // this[2] = z
    out[3] = scalar * this->w;  // this[3] = w
}