// FUNC_NAME: Triangle3D::computeNormal
// Address: 0x00522150
// Computes the normalized normal of a triangle defined by three vertices stored at offsets +0x0, +0x10, +0x20 from 'this'.
// Returns true if the normal length is >= DAT_00e44598 (valid triangle), false otherwise.
// The normalized normal is written to outNormal (param_1). outNormal[3] is always set to 0.0.

bool __thiscall Triangle3D::computeNormal(float *this, float *outNormal)
{
    // Triangle vertices (this): p0 at [0], p1 at [1], p2 at [2]? Actually offsets:
    // p0 = (this[0], this[1], this[2])   // +0x00
    // p1 = (this[4], this[5], this[6])   // +0x10
    // p2 = (this[8], this[9], this[10])  // +0x20
    float edge1x = this[4] - this[0];
    float edge1y = this[5] - this[1];
    float edge1z = this[6] - this[2];
    
    float edge2x = this[8] - this[0];
    float edge2y = this[9] - this[1];
    float edge2z = this[10] - this[2];
    
    // Cross product: edge1 x edge2
    outNormal[0] = edge1y * edge2z - edge1z * edge2y;
    outNormal[1] = edge1z * edge2x - edge1x * edge2z;
    outNormal[2] = edge1x * edge2y - edge1y * edge2x;
    
    // Normalize and check length
    float lenSq = outNormal[0] * outNormal[0] + outNormal[1] * outNormal[1] + outNormal[2] * outNormal[2];
    
    float invLen;
    float length;
    if (lenSq <= DAT_00e2cbe0) // epsilon for degenerate triangle
    {
        length = 0.0f;
        invLen = 0.0f;
    }
    else
    {
        length = sqrtf(lenSq);
        invLen = DAT_00e2b1a4 / length; // likely 1.0f for unit normal
    }
    
    bool valid = (DAT_00e44598 <= length);
    
    outNormal[0] *= invLen;
    outNormal[1] *= invLen;
    outNormal[2] *= invLen;
    
    // The decompiler shows a redundant assignment to outNormal[3], likely a compiler artifact (always zeroed)
    outNormal[3] = 0.0f;
    
    return valid;
}