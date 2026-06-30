// FUNC_NAME: DampingFilter::applyDamping
void __thiscall DampingFilter::applyDamping(uint channelCount, float dampingFactor)
{
    // This function applies a damping factor to a set of channels.
    // Each channel stores a current value and a previous value.
    // The previous value is updated to the old current, then the current is multiplied by dampingFactor.
    // Channels are stored in blocks of 4, each block is 0xC0 bytes.
    // Within a block, channels are at offsets: +0x0c, +0x3c, +0x6c, +0x9c (previous) and +0x1c, +0x4c, +0x7c, +0xac (current).
    // Channel stride is 0x30 bytes.

    int remaining = channelCount - 1;
    if (channelCount > 3)
    {
        // Process in groups of 4 channels (one block)
        int blockCount = channelCount >> 2;
        remaining = remaining + blockCount * -4;
        do
        {
            // Block of 4 channels at offset 0x00, 0x30, 0x60, 0x90 relative to block start
            // Each channel: previous at +0x0c, current at +0x1c
            *(float *)(this + 0x0c) = *(float *)(this + 0x1c);
            *(float *)(this + 0x1c) = *(float *)(this + 0x1c) * dampingFactor;

            *(float *)(this + 0x3c) = *(float *)(this + 0x4c);
            *(float *)(this + 0x4c) = *(float *)(this + 0x4c) * dampingFactor;

            *(float *)(this + 0x6c) = *(float *)(this + 0x7c);
            *(float *)(this + 0x7c) = *(float *)(this + 0x7c) * dampingFactor;

            *(float *)(this + 0x9c) = *(float *)(this + 0xac);
            *(float *)(this + 0xac) = *(float *)(this + 0xac) * dampingFactor;

            this = (char *)this + 0xC0; // Advance to next block
            blockCount--;
        } while (blockCount != 0);
    }

    // Process remaining channels (0 to 3)
    if (remaining >= 0)
    {
        float *current = (float *)(this + 0x1c);
        do
        {
            // current[-4] is the previous value (offset -0x10 from current)
            current[-4] = *current;
            *current = *current * dampingFactor;
            current += 0xC; // Advance to next channel (0x30 bytes / 4 = 0xC floats)
            remaining--;
        } while (remaining >= 0);
    }
}