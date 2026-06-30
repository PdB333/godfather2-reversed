// FUNC_NAME: Vector4::add
void __fastcall Vector4::add(float *thisResult, float *a, float *b)
{
    // This function adds two 4-component vectors (param2 + param3) and stores the result in param1 (in_EAX)
    // Note: The last component (w) is overwritten with the original w value from thisResult, likely to preserve it
    float aY = a[1]; // +0x04
    float aZ = a[2]; // +0x08
    float aW = a[3]; // +0x0C
    float bY = b[1]; // +0x04
    float bZ = b[2]; // +0x08
    float bW = b[3]; // +0x0C
    float thisW = thisResult[3]; // +0x0C, save original w

    thisResult[0] = a[0] + b[0]; // +0x00, x component
    thisResult[1] = aY + bY;     // +0x04, y component
    thisResult[2] = aZ + bZ;     // +0x08, z component
    thisResult[3] = aW + bW;     // +0x0C, w component (temporary)
    thisResult[3] = thisW;       // +0x0C, restore original w (likely treating as homogeneous coordinate)
}