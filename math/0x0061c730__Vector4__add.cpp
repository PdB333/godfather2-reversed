// FUNC_NAME: Vector4::add
// Function address: 0x0061c730
// Role: Adds two 4-component vectors (x,y,z,w) and stores result in output buffer.

void __thiscall Vector4::add(float *other, float *out) const
{
    // this[0..3] is the implicit first vector (x,y,z,w)
    // other[0..3] is the second vector
    // out[0..3] receives the sum
    out[0] = this[0] + other[0];  // x
    out[1] = this[1] + other[1];  // y
    out[2] = this[2] + other[2];  // z
    out[3] = this[3] + other[3];  // w
}