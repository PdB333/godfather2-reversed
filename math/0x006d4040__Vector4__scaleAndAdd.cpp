// FUNC_NAME: Vector4::scaleAndAdd
// Function address: 0x006d4040
// Purpose: Computes out = scale * this + v, where this, v are 4D vectors (float[4]).
// This is a multiply-add (MAD) operation common in vector math.
void __thiscall Vector4::scaleAndAdd(float *v, float scale, float *out)
{
    // Load components of 'this' vector (v1)
    float v1x = this[0];
    float v1y = this[1];
    float v1z = this[2];
    float v1w = this[3];
    
    // Load components of input vector v (v2)
    float v2x = v[0];
    float v2y = v[1];
    float v2z = v[2];
    float v2w = v[3];
    
    // Compute result: out = scale * v1 + v2
    out[0] = scale * v1x + v2x;
    out[1] = scale * v1y + v2y;
    out[2] = scale * v1z + v2z;
    out[3] = scale * v1w + v2w;
}