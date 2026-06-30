// FUNC_NAME: SoundInstance::computeAttenuation
// Address: 0x006d7ea0
// Computes the volume attenuation factor for a sound instance based on 2D distance from listener.
// Uses piecewise linear interpolation between inner/outer volume parameters.

void __thiscall SoundInstance::computeAttenuation(SoundInstance* this, float* outVolume)
{
    // m_soundState at +0x260: 0 and 0x48 indicate inactive states
    int soundState = *(int*)((uint8_t*)this + 0x260);
    if (soundState == 0 || soundState == 0x48)
        return;

    // Get listener position (2D: x,z) via a scratch buffer function
    float scratchBuf[6]; // 24 bytes, unused but required by the function
    uint8_t* listenerData = (uint8_t*)FUN_00424fb0(scratchBuf, 0);
    float listenerX = *(float*)(listenerData);
    float listenerZ = *(float*)(listenerData + 4);

    // Source index derived from soundState: offset by 0x48
    int sourceIndex = (soundState == 0) ? 0 : (soundState - 0x48);

    // Get sound source position (2D: x,z)
    float sourcePos[2];
    bool success = FUN_006c8620(sourcePos, sourceIndex, 4);
    if (!success)
        return;

    float sourceX = sourcePos[0];
    float sourceZ = sourcePos[1]; // stored at local_20 in original

    // 2D distance calculation
    float dx = sourceX - listenerX;
    float dz = sourceZ - listenerZ;
    float distance = sqrtf(dx*dx + dz*dz);

    float maxDistance = *(float*)((uint8_t*)this + 0x130); // m_maxDistance

    extern float g_maxHearingRange; // DAT_00e511c0, global maximum range
    extern float g_maxVolume;       // _DAT_00d5780c, clamp upper bound

    float ratio;
    if (maxDistance <= distance)
    {
        // Beyond max distance: normalize between maxDistance and global max
        ratio = (distance - maxDistance) / (g_maxHearingRange - maxDistance);
    }
    else
    {
        // Within max distance: simple proportion
        ratio = distance / maxDistance;
    }

    // Clamp ratio to [0, g_maxVolume]
    if (ratio <= 0.0f)
        ratio = 0.0f;
    else if (g_maxVolume <= ratio)
        ratio = g_maxVolume;

    // Attenuation parameters based on distance zone
    float paramA, paramB;
    if (maxDistance <= distance)
    {
        // Beyond max distance: use +0x128 (outer) and +0x124 (inner)
        paramB = *(float*)((uint8_t*)this + 0x128); // +0x128: outer volume/radius
        paramA = *(float*)((uint8_t*)this + 0x124); // +0x124: inner volume/radius
    }
    else
    {
        // Within max distance: use +0x128 and +0x12C (300)
        paramB = *(float*)((uint8_t*)this + 0x12C); // +0x12C: another attenuation parameter
        paramA = *(float*)((uint8_t*)this + 0x128); // +0x128: outer volume/radius
    }

    // Linear interpolation: result = (paramA - paramB) * ratio + paramB
    *outVolume = (paramA - paramB) * ratio + paramB;
}