// FUNC_NAME: SelectSmallerBuffer
// Address: 0x006fc0f0
// Role: Returns a pointer to one of two internal buffers (at offsets +0x180 and +0x1b8) based on which has the smaller associated size (offsets +0x1a4 and +0x1dc).
//       If sizes are equal, no output is written. The index (0 or 1) is stored in outBufferIndex.
//       Assumes param_2 is non-null; if null, function does nothing.
void __thiscall SelectSmallerBuffer(int *outBufferPtr, int *outBufferIndex)
{
    if (outBufferPtr != nullptr)
    {
        // +0x1a4: first size (unsigned)
        // +0x1dc: second size (unsigned)
        unsigned int firstSize = *(unsigned int *)(this + 0x1a4);
        unsigned int secondSize = *(unsigned int *)(this + 0x1dc);

        if (firstSize < secondSize)
        {
            // Return pointer to first buffer at +0x180
            *outBufferPtr = this + 0x180;
            *outBufferIndex = 0;
            return;
        }
        else if (secondSize < firstSize)
        {
            // Return pointer to second buffer at +0x1b8
            *outBufferPtr = this + 0x1b8;
            *outBufferIndex = 1;
            return;
        }
        // If sizes are equal, no output is set
    }
}