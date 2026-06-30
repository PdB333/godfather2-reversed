// FUNC_NAME: Entity::normalizeQuaternion
// Function at 0x00550a70
// Copies a 3-element direction vector from an external source (accessed via this+0x18->+0x160)
// into the object's quaternion at +0x90 (x,y,z) with w set to a global constant,
// then normalizes the quaternion (only using x,y,z for length).

void Entity::normalizeQuaternion(void)
{
    // Get source data pointer: *(int *)(this + 0x18) -> extra structure, then +0x160 yields base of source vector
    int* sourceData = *(int**)(*(int*)(this + 0x18) + 0x160);

    // Copy three floats at +0xe0, +0xe4, +0xe8 into this+0x90 (x), +0x94 (y), +0x98 (z)
    float qx = *(float*)(sourceData + 0xe0);
    float qy = *(float*)(sourceData + 0xe4);
    float qz = *(float*)(sourceData + 0xe8);
    *(float*)(this + 0x90) = qx;
    *(float*)(this + 0x94) = qy;
    *(float*)(this + 0x98) = qz;
    *(float*)(this + 0x9c) = DAT_00e2b1a4;  // w component, from global constant (likely 0.0f)

    // Normalization using only x,y,z components (w not included in squared length)
    float x = *(float*)(this + 0x90);
    float y = *(float*)(this + 0x94);
    float z = *(float*)(this + 0x98);
    float w = *(float*)(this + 0x9c);
    float lenSq = x*x + y*y + z*z;

    if (lenSq == 0.0f) {
        lenSq = 0.0f;
    } else {
        // fast inverse sqrt approximation (FUN_00414a80)
        float invLen = fastInvSqrt(lenSq);
        x *= invLen;
        y *= invLen;
        z *= invLen;
        w *= invLen;
    }

    // Store normalized components
    *(float*)(this + 0x90) = x;
    *(float*)(this + 0x94) = y;
    *(float*)(this + 0x98) = z;
    *(float*)(this + 0x9c) = w;

    return;
}