// FUNC_NAME: Vector4::lerp
// Function address: 0x006d00c0
// Linear interpolation between two 4-component vectors (quaternion or position)
// this = start vector (a), param_1 = end vector (b), param_2 = interpolation factor (t), param_3 = output (result)
// result[i] = (b[i] - a[i]) * t + a[i] for i=0..3

void __thiscall Vector4::lerp(const float* end, float t, float* result) const
{
    // Load start components from this (implicit pointer in EAX)
    float startX = this[0];
    float startY = this[1];
    float startZ = this[2];
    float startW = this[3];

    // Load end components from pointer passed as param_1
    float endX = end[0];
    float endY = end[1];
    float endZ = end[2];
    float endW = end[3];

    // Compute interpolated components into output (param_3)
    result[0] = (endX - startX) * t + startX;
    result[1] = (endY - startY) * t + startY;
    result[2] = (endZ - startZ) * t + startZ;
    result[3] = (endW - startW) * t + startW;
}