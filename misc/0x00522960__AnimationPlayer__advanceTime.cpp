// FUNC_NAME: AnimationPlayer::advanceTime
// Address: 0x00522960
// Role: Advance animation playback time and compute interpolated transform parameters.
// Called each frame with a delta time to update the animation state.
int __thiscall AnimationPlayer::advanceTime(float deltaTime)
{
    // 'this' is at param_1
    // +0x14: accumulated time (elapsed)
    // +0x10: pointer to the animation clip data (ClipData)
    float newTime = deltaTime + *(float *)(this + 0x14);
    ClipData* clip = *(ClipData**)(this + 0x10);
    *(float *)(this + 0x14) = newTime;

    uint3 statusBits = (uint3)((uint)clip >> 8); // extract high bits for status

    if (newTime < *(float *)(clip + 0x6c)) // duration check
    {
        // Compute interpolated blend value
        float blendMin = *(float *)(clip + 0x94);
        float blendVal1 = newTime * *(float *)(clip + 0x88) + *(float *)(clip + 0x84); // x blend
        float blendVal2 = newTime * *(float *)(clip + 0x90) + *(float *)(clip + 0x8c); // y blend
        if (blendVal1 < blendVal2)
        {
            blendVal2 = blendVal1;
        }
        float blend = blendVal2;
        if (blendMin <= blend && blend > *(float *)(clip + 0x98))
        {
            blend = *(float *)(clip + 0x98); // clamp to max
        }
        *(float *)(this + 0x18) = blend;

        // Compute base position offsets
        float posX = *(float *)(clip + 0x54) * newTime;
        float posY = *(float *)(clip + 0x58) * newTime;
        *(float *)(this + 0x28) = posX;
        *(float *)(this + 0x2c) = posY;

        // Apply sub-pixel adjustment if flag not set
        if ((*(ushort *)(clip + 0x44) & 0x2000) == 0)
        {
            float dx = (posX - (int)posX) * *(float *)(clip + 0x4c);
            float dy = (posY - (int)posY) * *(float *)(clip + 0x50);
            // Fractional part times some multiplier, then scaled by extra scale factors
            *(float *)(this + 0x28) = (float)(int)dx * *(float *)(clip + 0xb0);
            *(float *)(this + 0x2c) = (float)(int)dy * *(float *)(clip + 0xb4);
        }

        // Compute scale factors from range interpolation
        float rangeX = *(float *)(clip + 0x64) * newTime + *(float *)(clip + 0x5c);
        float rangeY = *(float *)(clip + 0x68) * newTime + *(float *)(clip + 0x60);
        if ((double)rangeX < DAT_00e446c8) // threshold
        {
            rangeX = DAT_00e2e210; // fallback value (likely 1.0f)
        }
        if ((double)rangeY < DAT_00e446c8)
        {
            rangeY = DAT_00e2e210;
        }
        float invScaleY = DAT_00e2b1a4 / rangeY;
        *(float *)(this + 0x30) = DAT_00e2b1a4 / rangeX;
        *(float *)(this + 0x34) = invScaleY;

        // Return status: combine extracted high bits with a 1 in the low byte
        return CONCAT31(statusBits, 1);
    }
    // Time exceeded duration -> return finished status (low byte zero)
    return (uint)statusBits << 8;
}