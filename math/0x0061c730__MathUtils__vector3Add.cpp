// FUNC_NAME: MathUtils::vector3Add
void __thiscall vector3Add(float *this, float *vecA, float *result)
{
    float x1, y1, z1, w1;
    float x2, y2, z2, w2;

    // Extract components from the first vector (this pointer via in_EAX)
    // +0x00: x, +0x04: y, +0x08: z, +0x0C: w (homogeneous or padding)
    x1 = this[0];      // +0x00
    y1 = this[1];      // +0x04
    z1 = this[2];      // +0x08
    w1 = this[3];      // +0x0C

    // Extract components from the second vector (param_1/vecA)
    // +0x00: x, +0x04: y, +0x08: z, +0x0C: w
    x2 = vecA[0];
    y2 = vecA[1];
    z2 = vecA[2];
    w2 = vecA[3];

    // Store result (param_2/result)
    result[0] = x1 + x2;  // +0x00: result.x
    result[1] = y1 + y2;  // +0x04: result.y
    result[2] = z1 + z2;  // +0x08: result.z
    result[3] = w1 + w2;  // +0x0C: result.w (typically 1.0f after addition)
}