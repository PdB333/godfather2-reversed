// FUNC_NAME: Math::lerpQuaternion
void __fastcall Math::lerpQuaternion(float *outQuat, float *quatA, float *quatB, float t)
{
    // Interpolate quaternion components: out = t * quatA + (1-t) * quatB
    // But note: the original code stores quatB first, then adds scaled quatA
    // and overwrites the w component with quatA's w at the end (likely a bug or specific blending)
    float ax = quatA[0]; // +0x00
    float ay = quatA[1]; // +0x04
    float az = quatA[2]; // +0x08
    float aw = quatA[3]; // +0x0C
    float bx = quatB[0]; // +0x00
    float by = quatB[1]; // +0x04
    float bz = quatB[2]; // +0x08
    float bw = quatB[3]; // +0x0C

    outQuat[0] = bx + t * ax; // x = quatB.x + t * quatA.x
    outQuat[1] = by + t * ay; // y = quatB.y + t * quatA.y
    outQuat[2] = bz + t * az; // z = quatB.z + t * quatA.z
    outQuat[3] = bw + t * aw; // w = quatB.w + t * quatA.w
    outQuat[3] = aw;          // Override w with quatA's w (likely intentional for specific blending)
}