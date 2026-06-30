// FUNC_NAME: Animation::playAnimation

void Animation::playAnimation()
{
    // this+0x23: animation flags (byte)
    uint animFlags = *(byte*)(this + 0x23);
    uint blendType = (animFlags & 1) ? 2 : 0;

    // Virtual call at vtable+0x1c: returns pointer to animation set data
    undefined4* animSet = (undefined4*)(this->vtable[0x1c])();

    int animState = *(int*)(this + 0x20); // +0x20: current animation state/type

    if (animState == 0 || animState == 0x48) // 0x48 = 72, likely a specific animation type
    {
        // Check if the four animation IDs at +0x1c..+0x1f are all zero
        if (*(int*)(this + 0x1c) == 0 && *(int*)(this + 0x1d) == 0 &&
            *(int*)(this + 0x1e) == 0 && *(int*)(this + 0x1f) == 0)
        {
            if (*(int*)(this + 0x22) == -1) // +0x22: some flag, -1 means no override
            {
                int animIndex = 0;
                goto playAnim;
            }
            // Otherwise, queue an animation request
            int stackVar = *(int*)(this + 0x16); // +0x16: current animation index?
            byte stackByte = 0;
            undefined4* stackPtr = animSet;
            queueAnimationRequest(&stackVar, animFlags); // FUN_0043c740
            goto cleanup;
        }
        else
        {
            // Get animation data from the four IDs
            int* animData = getAnimationData((int*)(this + 0x1c), 0); // FUN_00445ff0
            if (animData != 0 && (*(uint*)(animData + 0x14) & 0x8000000) != 0)
            {
                int animIndex = (int)animData + 0x3c; // offset to animation index
                goto playAnim;
            }
            goto cleanup;
        }
    }
    else
    {
        // Fallback: if animState is 0 or 0x48 (redundant check, likely decompiler artifact)
        if (animState == 0 || animState == 0x48)
        {
            int animIndex = 0;
            goto playAnim;
        }
    }

playAnim:
    setAnimation(this + 0x16, animIndex, 0, animSet, blendType); // FUN_00440590

cleanup:
    if (animSet != 0)
    {
        (*(void (**)(undefined4*, int))*animSet)(animSet, 1); // release animSet
    }
}