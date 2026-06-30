// FUNC_NAME: PlayerSM::changeAnimationByAction
void __thiscall PlayerSM::changeAnimationByAction(int thisPtr, int actionType)
{
    // +0x2d8: flags (bit0x20 = customAnimationFlag, bit0x8 = animationUpdated)
    uint flags = *(uint*)(thisPtr + 0x2d8);
    flags |= 0x20; // indicate we are about to set an animation
    *(uint*)(thisPtr + 0x2d8) = flags;

    // +0x380: bool indicating whether to use custom animation table
    bool useCustomAnimations = *(char*)(thisPtr + 0x380) != 0;

    if (useCustomAnimations) {
        // Map action type to custom animation index (0-4)
        int animIndex = 0;
        switch (actionType) {
        case 0:
        case 1:
            animIndex = 0;
            break;
        case 2:
        case 3:
            animIndex = 1;
            break;
        case 4:
            animIndex = 2;
            break;
        case 5:
            animIndex = 3;
            break;
        case 6:
        case 7:
            animIndex = 4;
            break;
        // no default; unhandled values leave animIndex=0
        }

        // +0x3a0: array of 5 animation data structs, each 0x1c bytes
        int src = thisPtr + 0x3a0 + animIndex * 0x1c;
        // +0x46c: current animation data (28 bytes)
        *(uint64*)(thisPtr + 0x46c) = *(uint64*)src;
        *(uint64*)(thisPtr + 0x474) = *(uint64*)(src + 8);
        *(uint64*)(thisPtr + 0x47c) = *(uint64*)(src + 0x10);
        *(uint32*)(thisPtr + 0x484) = *(uint32*)(src + 0x18);
    } else {
        // +0x384: default animation data (28 bytes)
        *(uint64*)(thisPtr + 0x46c) = *(uint64*)(thisPtr + 0x384);
        *(uint64*)(thisPtr + 0x474) = *(uint64*)(thisPtr + 0x38c);
        *(uint64*)(thisPtr + 0x47c) = *(uint64*)(thisPtr + 0x394);
        *(uint32*)(thisPtr + 0x484) = *(uint32*)(thisPtr + 0x39c);
    }

    // Set flag indicating animation data was updated
    flags = *(uint*)(thisPtr + 0x2d8);
    flags |= 8;
    *(uint*)(thisPtr + 0x2d8) = flags;
}