// FUNC_NAME: MathUtil::addVec3PreserveW
void __fastcall MathUtil::addVec3PreserveW(float* out, float* vecA, float* vecB)
{
    // Adds two 3-component vectors (x,y,z) and stores result in out, preserving out[3] (w).
    // This is typical for operations where the w component should remain independent.
    // The first parameter (ECX, "this" in __fastcall) is unused, suggesting a static method.
    // Parameters: out (destination, passed in EAX), vecA (EDX), vecB (pushed on stack).
    
    float aY = vecA[1]; // +0x04
    float aZ = vecA[2]; // +0x08
    float aW = vecA[3]; // +0x0C (unused in addition but read)
    float bY = vecB[1]; // +0x04
    float bZ = vecB[2]; // +0x08
    float bW = vecB[3]; // +0x0C (unused)
    float oldW = out[3]; // +0x0C preserve original w

    out[0] = vecA[0] + vecB[0]; // x
    out[1] = aY + bY;           // y
    out[2] = aZ + bZ;           // z
    out[3] = oldW;              // restore w unchanged
}