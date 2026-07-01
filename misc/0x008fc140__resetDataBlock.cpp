// FUNC_NAME: resetDataBlock
// Address: 0x008fc140
// Role: Checks if a 16-byte block (4 ints) is all zero, and if not, calls a zeroing function to clear it.
// Likely a cleanup/reset for a small structure or bitfield.
void resetDataBlock(int* dataBlock)
{
    // Check if any of the first four ints are non-zero
    if ((dataBlock[0] != 0) || (dataBlock[1] != 0) || (dataBlock[2] != 0) || (dataBlock[3] != 0))
    {
        // Zero out the block (FUN_00446100 is presumably a memset-like function with size 0)
        FUN_00446100(dataBlock, 0);
    }
}