// FUNC_NAME: MathUtils::lerpQuaternion
void __fastcall MathUtils::lerpQuaternion(float *outQuat, float *fromQuat, float *toQuat, float t)
{
    float fromX, fromY, fromZ, fromW;
    float toX, toY, toZ, toW;

    fromX = fromQuat[1]; // +0x04
    fromY = fromQuat[2]; // +0x08
    fromZ = fromQuat[3]; // +0x0C
    fromW = outQuat[3];  // Preserve original w component? (likely a bug or intentional)
    toX = toQuat[1];     // +0x04
    toY = toQuat[2];     // +0x08
    toZ = toQuat[3];     // +0x0C

    outQuat[0] = t * fromQuat[0] + toQuat[0]; // +0x00
    outQuat[1] = t * fromX + toX;             // +0x04
    outQuat[2] = t * fromY + toY;             // +0x08
    outQuat[3] = t * fromZ + toZ;             // +0x0C
    outQuat[3] = fromW;                       // Restore original w (overwrites lerp result)
}