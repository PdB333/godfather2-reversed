// FUNC_NAME: Animation::stop
void __thiscall Animation::stop(int thisPtr)
{
    // Check if bit 12 (0x1000) is set in flags at +0x60
    if ((*(uint *)(thisPtr + 0x60) >> 0xc & 1) != 0) {
        // Clear playback handle at +0x130
        *(int *)(thisPtr + 0x130) = 0;
        // Stop the animation stream/object pointed by +0x12C
        FUN_009c8f10(*(int *)(thisPtr + 0x12C));  // likely AnimationStream::stop or similar
        // Clear stream pointer at +0x12C
        *(int *)(thisPtr + 0x12C) = 0;
        // Clear aux field at +0x134
        *(int *)(thisPtr + 0x134) = 0;
        // Clear the flag bit
        *(uint *)(thisPtr + 0x60) &= 0xFFFFEFFF;
    }
}