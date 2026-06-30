// FUNC_NAME: Vector4::addScaledVector
// Address: 0x0051e320
// Role: Linear combination of two 4D vectors: out = v + t * this
// This function takes the implicit 'this' as one vector, a scalar t, and a second vector v,
// and writes the result to the output pointer.

void __thiscall Vector4::addScaledVector(float *this, float t, float *v, float *out)
{
    out[0] = t * this[0] + v[0];
    out[1] = t * this[1] + v[1];
    out[2] = t * this[2] + v[2];
    out[3] = t * this[3] + v[3];
}