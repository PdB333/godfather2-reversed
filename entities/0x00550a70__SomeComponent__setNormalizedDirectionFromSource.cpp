// FUNC_NAME: SomeComponent::setNormalizedDirectionFromSource

void SomeComponent::setNormalizedDirectionFromSource()
{
    // Get pointer to source object via (this + 0x18) -> +0x160
    int* sourceObj = *(int**)((char*)this + 0x18);
    float* sourceVec = (float*)(sourceObj[0x160 / 4]); // sourceVec points to 3 floats at offsets 0xe0,0xe4,0xe8

    // Copy source x,y,z and set w from global constant (likely 0.0)
    float xSrc = sourceVec[0xe0 / 4];
    float ySrc = sourceVec[0xe4 / 4];
    float zSrc = sourceVec[0xe8 / 4];
    float wSrc = DAT_00e2b1a4; // Some constant (probably 0.0)

    // Store into this + 0x90,0x94,0x98,0x9c
    *(float*)((char*)this + 0x90) = xSrc;
    *(float*)((char*)this + 0x94) = ySrc;
    *(float*)((char*)this + 0x98) = zSrc;
    *(float*)((char*)this + 0x9c) = wSrc;

    // Compute length squared of (x,y,z) only
    float lenSq = xSrc*xSrc + ySrc*ySrc + zSrc*zSrc;
    float invLen;
    if (lenSq == 0.0f)
    {
        invLen = 0.0f;
    }
    else
    {
        // sqrtf (address 0x00414a80)
        float len = sqrtf(lenSq);
        invLen = 1.0f / len;
    }

    // Scale all four components by inverse length to normalize
    *(float*)((char*)this + 0x90) = xSrc * invLen;
    *(float*)((char*)this + 0x94) = ySrc * invLen;
    *(float*)((char*)this + 0x98) = zSrc * invLen;
    *(float*)((char*)this + 0x9c) = wSrc * invLen;
}