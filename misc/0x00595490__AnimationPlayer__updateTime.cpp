// FUNC_NAME: AnimationPlayer::updateTime
void AnimationPlayer::updateTime(float deltaTime)
{
    // Structure layout at this pointer (float*):
    // +0x00: float currentTime (accumulated play time)
    // +0x04: uint16 currentIndex
    // +0x06: uint16 totalKeys
    // +0x08: uint16 playbackMode (0..3)
    // +0x0C: float* keyframeData (array of keyframe structures)

    float* thisPtr = reinterpret_cast<float*>(this); // this is in EAX
    float accumulatedTime = *thisPtr;                 // currentTime
    accumulatedTime += deltaTime;
    *thisPtr = accumulatedTime;

    uint16* fields = reinterpret_cast<uint16*>(thisPtr + 1); // offset +4
    uint16 currentIndex = fields[0];   // +0x04
    uint16 totalKeys = fields[1];     // +0x06 (note: offset +6)
    uint16 mode = fields[2];          // +0x08
    float* keyframes = *reinterpret_cast<float**>(thisPtr + 3); // +0x0C

    uint16 newIndex = currentIndex;
    uint32 stride = 0;

    switch (mode)
    {
    case 0: // stride 8 bytes (2 floats)
        stride = 8;
        // Check if time fell behind the previous keyframe
        if (accumulatedTime < *(float*)((uint8*)keyframes + (newIndex * stride) - stride))
        {
            newIndex = 1;
        }
        // Advance while the current keyframe time is <= accumulated time
        if (newIndex < totalKeys)
        {
            while (*(float*)((uint8*)keyframes + newIndex * stride) <= accumulatedTime)
            {
                newIndex++;
                if (newIndex >= totalKeys)
                {
                    newIndex = totalKeys; // clamp? but the original returns
                    break;
                }
            }
        }
        break;

    case 1: // stride 16 bytes (4 floats)
        stride = 16;
        if (accumulatedTime < *(float*)((uint8*)keyframes + (newIndex * stride) - stride))
        {
            newIndex = 1;
        }
        if (newIndex < totalKeys)
        {
            while (*(float*)((uint8*)keyframes + newIndex * stride) <= accumulatedTime)
            {
                newIndex++;
                if (newIndex >= totalKeys) return; // early return in original
            }
        }
        break;

    case 2: // stride 20 bytes (5 floats)
        stride = 20;
        if (accumulatedTime < *(float*)((uint8*)keyframes + (newIndex * stride) - stride))
        {
            newIndex = 1;
        }
        if (newIndex < totalKeys)
        {
            while (*(float*)((uint8*)keyframes + newIndex * stride) <= accumulatedTime)
            {
                newIndex++;
                if (newIndex >= totalKeys) return;
            }
        }
        break;

    case 3: // stride 24 bytes (6 floats)
        stride = 24;
        if (accumulatedTime < *(float*)((uint8*)keyframes + (newIndex * stride) - stride))
        {
            newIndex = 1;
        }
        if (newIndex < totalKeys)
        {
            // do-while variant: checks condition after increment? 
            // Actually original uses a do-while loop without break if condition false at start
            // Replicate: while (newIndex < totalKeys) { if (accumulatedTime < keyframe) return; newIndex++; }
            while (newIndex < totalKeys)
            {
                if (accumulatedTime < *(float*)((uint8*)keyframes + newIndex * stride))
                {
                    break;
                }
                newIndex++;
            }
        }
        break;
    }

    // Write back the potentially updated index
    fields[0] = newIndex;
    return;
}