// FUNC_NAME: Vector4::subtract
void __thiscall Vector4::subtract(const float* other, float* result) const
{
    // Subtract the 'other' vector from this vector element-wise
    // and store the result in 'result'.
    // This: [x, y, z, w] (via this pointer)
    // Other: other[0..3] (passed as param_1)
    // Result: result[0..3] (passed as param_2)
    float thisY = y;
    float thisZ = z;
    float thisW = w;
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];

    result[0] = x - other[0];
    result[1] = thisY - otherY;
    result[2] = thisZ - otherZ;
    result[3] = thisW - otherW;
}