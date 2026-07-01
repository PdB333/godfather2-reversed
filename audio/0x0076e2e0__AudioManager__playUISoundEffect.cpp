// FUNC_NAME: AudioManager::playUISoundEffect
void __thiscall AudioManager::playUISoundEffect(int *this, uint id, bool isActive) {
    int *objPtr;
    
    objPtr = (int *)this[0x14];                         // +0x50: pointer to some large object
    // Check sound IDs against category values stored in the object at various offsets
    if (id == (*(uint *)(objPtr + 0x68c) >> 2) || id == (*(uint *)(objPtr + 0x6b4) >> 2) ||
        id == (*(uint *)(objPtr + 0x674) >> 2))
    {
        // Category A sounds (e.g., generic selection)
        if (!isActive)
            playSound(0x76ab6c71, 1, 1, 0, 1.0f, 1.0f); // "off" sound
        else
            playSound(0x8de4ca5d, 1, 1, 0, 1.0f, 1.0f); // "on" sound
        return;
    }
    if (id == (*(uint *)(objPtr + 0x670) >> 2)) {
        // Category B (single sound for both states)
        if (isActive) {
            playSound(0x8de4ca5d, 1, 1, 0, 1.0f, 1.0f); // same as "on" from above
            return;
        }
    } else if (id == (*(uint *)(objPtr + 0x6b8) >> 2)) {
        // Category C (another single sound)
        if (isActive) {
            playSound(0x19b1d3f6, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
    } else {
        // Check multiple categories with pairs
        if (id == (*(uint *)(objPtr + 0x678) >> 2) || id == (*(uint *)(objPtr + 0x67c) >> 2) ||
            id == (*(uint *)(objPtr + 0x680) >> 2) || id == (*(uint *)(objPtr + 0x684) >> 2) ||
            id == (*(uint *)(objPtr + 0x688) >> 2))
        {
            if (!isActive)
                playSound(0x27cff3b5, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0x1162e8c9, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        if (id == (*(uint *)(objPtr + 0x6a0) >> 2) || id == (*(uint *)(objPtr + 0x6a4) >> 2) ||
            id == (*(uint *)(objPtr + 0x6a8) >> 2) || id == (*(uint *)(objPtr + 0x6ac) >> 2) ||
            id == (*(uint *)(objPtr + 0x6b0) >> 2))
        {
            if (!isActive)
                playSound(0x11f9838e, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0x8237d37a, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        if (id == (*(uint *)(objPtr + 0x66c) >> 2) || id == (*(uint *)(objPtr + 0x668) >> 2) ||
            id == (*(uint *)(objPtr + 0x664) >> 2) || id == (*(uint *)(objPtr + 0x660) >> 2))
        {
            if (!isActive)
                playSound(0x2d309f32, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0xd752846, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
        if (id == (*(uint *)(objPtr + 0x69c) >> 2) || id == (*(uint *)(objPtr + 0x698) >> 2) ||
            id == (*(uint *)(objPtr + 0x694) >> 2) || id == (*(uint *)(objPtr + 0x690) >> 2))
        {
            if (!isActive)
                playSound(0x1040b751, 1, 1, 0, 1.0f, 1.0f);
            else
                playSound(0xca32733d, 1, 1, 0, 1.0f, 1.0f);
            return;
        }
    }
    // Default sound for category B or C when isActive is false
    playSound(0x5d8c4a78, 1, 1, 0, 1.0f, 1.0f);
}