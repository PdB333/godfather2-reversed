// FUNC_NAME: MathUtil::vector2DFunction
void MathUtil::vector2DFunction(const float* p1, const float* p2, float arg1, float arg2, float arg3)
{
    // Extract two floats from each pointer: field0 and field8 (assuming 3D vector with x,y,z; taking x and z)
    float x1 = p1[0];  // +0x00
    float z1 = p1[2];  // +0x08
    float x2 = p2[0];  // +0x00
    float z2 = p2[2];  // +0x08

    // Call the core operation with 2D vector data
    FUN_005f6ee0(&x1, &x2, arg1, arg2, arg3);
    // Note: The underlying function likely modifies the values in place or computes a result
}