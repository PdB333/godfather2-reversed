// FUNC_NAME: GameplayHelper::checkProgressionAndPackHandle
int __fastcall GameplayHelper::checkProgressionAndPackHandle(int thisObj)
{
    // Read handle from global game manager singleton
    int handle = **((int**)(*(int*)(0x012233a0) + 4));
    float fValue = *(float*)(thisObj + 0x54);

    // If handle is valid after adjusting for component offset
    if (handle != 0)
    {
        handle -= 0x1f30; // Adjust to pointer component
        if (handle != 0)
        {
            // Compute blended float: (current + rate) * globalScale, then pulled toward rate
            fValue = (fValue + *(float*)(thisObj + 0x58)) * *(float*)0x00d5c458;
            fValue = fValue - (*(float*)(thisObj + 0x58) - fValue);
            if (fValue < 0.0f)
                fValue = 0.0f;
        }
    }

    // Pack the handle's upper 24 bits into the high part of result
    unsigned int highPart = ((unsigned int)handle) >> 8;

    // Check threshold at offset 0x40
    float threshold = *(float*)(thisObj + 0x40);
    if (threshold <= fValue && fValue != threshold)
    {
        // Set low byte to 1 to indicate above threshold
        return (highPart & 0xFFFFFF00) | 1;
    }

    // Return with low byte 0
    return highPart << 8;
}