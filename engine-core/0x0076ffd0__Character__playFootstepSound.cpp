// FUNC_NAME: Character::playFootstepSound
void __fastcall Character::playFootstepSound(int *this)
{
    uint surfaceType = this[0x25]; // +0x94: surface type ID
    char randomFlag = getRandomFlag(); // FUN_0076ec60 - random boolean
    int *worldData = (int *)this[0x14]; // +0x50: pointer to world data structure

    // Check surface type against various material groups (offsets in worldData)
    if (((surfaceType == worldData[0x68c / 4] >> 2) || 
         (surfaceType == worldData[0x6b4 / 4] >> 2) ||
         (surfaceType == worldData[0x674 / 4] >> 2)))
    {
        // Group A: e.g., concrete, asphalt
        int soundId = (randomFlag != 0) ? 0x76ab6c71 : 0x17395dec;
        playSoundEvent(soundId, 1, 1, 0, 1.0f, 1.0f);
    }
    else if (((surfaceType == worldData[0x678 / 4] >> 2) || 
              (surfaceType == worldData[0x67c / 4] >> 2) ||
              (surfaceType == worldData[0x680 / 4] >> 2) ||
              (surfaceType == worldData[0x684 / 4] >> 2) ||
              (surfaceType == worldData[0x688 / 4] >> 2)))
    {
        // Group B: e.g., wood, metal
        int soundId = (randomFlag != 0) ? 0x27cff3b5 : 0xe992f514;
        playSoundEvent(soundId, 1, 1, 0, 1.0f, 1.0f);
    }
    else if (((surfaceType == worldData[0x6a0 / 4] >> 2) || 
              (surfaceType == worldData[0x6a4 / 4] >> 2) ||
              (surfaceType == worldData[0x6a8 / 4] >> 2) ||
              (surfaceType == worldData[0x6ac / 4] >> 2) ||
              (surfaceType == worldData[0x6b0 / 4] >> 2)))
    {
        // Group C: e.g., grass, dirt
        // Special condition: check flag at this+0x54 bit 2 and worldData+0x1f58 bit 11
        if (((*(byte *)(this + 0x15) & 4) == 0) && ((worldData[0x1f58 / 4] >> 0xb & 1) != 0))
        {
            playSoundEvent(0xe00e1b0, 1, 1, 0, 1.0f, 1.0f);
        }
        else
        {
            int soundId = (randomFlag != 0) ? 0x11f9838e : 0x703e4fec;
            playSoundEvent(soundId, 1, 1, 0, 1.0f, 1.0f);
        }
    }
    else
    {
        // Check for other surface groups
        if ((surfaceType != worldData[0x6b8 / 4] >> 2) && 
            (surfaceType != worldData[0x670 / 4] >> 2))
        {
            // Group D: e.g., water, mud
            if ((surfaceType == worldData[0x66c / 4] >> 2) ||
                (surfaceType == worldData[0x668 / 4] >> 2) ||
                (surfaceType == worldData[0x664 / 4] >> 2) ||
                (surfaceType == worldData[0x660 / 4] >> 2))
            {
                if (randomFlag == 0)
                {
                    playSoundEvent(0x2d309f32, 1, 1, 0, 1.0f, 1.0f);
                    return;
                }
                playSoundEvent(0xd752846, 1, 1, 0, 1.0f, 1.0f);
                return;
            }
            // Group E: e.g., carpet, tile
            if ((surfaceType != worldData[0x69c / 4] >> 2) &&
                (surfaceType != worldData[0x698 / 4] >> 2) &&
                (surfaceType != worldData[0x694 / 4] >> 2) &&
                (surfaceType != worldData[0x690 / 4] >> 2))
            {
                return; // Unknown surface, no sound
            }
            if (randomFlag == 0)
            {
                playSoundEvent(0x1040b751, 1, 1, 0, 1.0f, 1.0f);
                return;
            }
            playSoundEvent(0xca32733d, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        // Group F: e.g., snow, sand
        int soundId = (randomFlag != 0) ? 0x5d8c4a78 : 0xbc25897e;
        playSoundEvent(soundId, 1, 1, 0, 1.0f, 1.0f);
    }
    // Clear footstep flag (bit 0 of byte at +0x54)
    *(byte *)(this + 0x15) &= 0xfe;
}