// FUNC_NAME: MathUtils::lerpQuaternion
void __fastcall lerpQuaternion(float *result, float *from, float *to, float t)
{
    float fromX, fromY, fromZ, fromW;
    float toX, toY, toZ, toW;

    fromX = from[0]; // +0x00
    fromY = from[1]; // +0x04
    fromZ = from[2]; // +0x08
    fromW = from[3]; // +0x0C

    toX = to[0]; // +0x00
    toY = to[1]; // +0x04
    toZ = to[2]; // +0x08
    toW = to[3]; // +0x0C

    // Linear interpolation of quaternion components
    result[0] = t * fromX + toX; // +0x00
    result[1] = t * fromY + toY; // +0x04
    result[2] = t * fromZ + toZ; // +0x08
    result[3] = t * fromW + toW; // +0x0C

    // Preserve original W component (likely for normalization or slerp fallback)
    result[3] = fromW;
}