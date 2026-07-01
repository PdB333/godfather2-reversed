// FUNC_NAME: DataBuffer::calculateUsedSize
// Function at 0x00897990: Calculates the total size of used data blocks in a buffer.
// The buffer has a 4-byte header (offset 0x00) followed by an array of 16-byte blocks.
// Each block is considered "empty" if it matches a specific magic pattern (0xBADBADBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911)
// or if all four ints are zero. Otherwise, the block is "used" and contributes 16 bytes to the total size.
// The function scans the buffer using a sliding window of 4 blocks per iteration, covering 7 iterations (28 blocks total).
// Returns the total size (4-byte header + 16 * number of used blocks encountered).

int __fastcall DataBuffer::calculateUsedSize(int thisPtr)
{
    int totalSize = 4; // Base size: 4-byte header at offset 0x00
    int* blockPtr = reinterpret_cast<int*>(thisPtr + 0x24); // Points to offset 0x24, likely start of sliding window
    int iterationCount = 7;

    do {
        // Check block at offset -32 from blockPtr (absolute offset 0x04)
        if ( !( (blockPtr[-8] == -0x45245246 && blockPtr[-7] == -0x41104111 && blockPtr[-6] == -0x153ea5ab && blockPtr[-5] == -0x6eeff6ef) ||
                (blockPtr[-8] == 0 && blockPtr[-7] == 0 && blockPtr[-6] == 0 && blockPtr[-5] == 0) ) )
        {
            totalSize += 0x10; // Block is used, add 16 bytes
        }

        // Check block at offset -8 from blockPtr (absolute offset 0x1C)
        if ( !( (blockPtr[-2] == -0x45245246 && blockPtr[-1] == -0x41104111 && blockPtr[0] == -0x153ea5ab && blockPtr[1] == -0x6eeff6ef) ||
                (blockPtr[-2] == 0 && blockPtr[-1] == 0 && blockPtr[0] == 0 && blockPtr[1] == 0) ) )
        {
            totalSize += 0x10;
        }

        // Check block at offset +16 from blockPtr (absolute offset 0x34)
        if ( !( (blockPtr[4] == -0x45245246 && blockPtr[5] == -0x41104111 && blockPtr[6] == -0x153ea5ab && blockPtr[7] == -0x6eeff6ef) ||
                (blockPtr[4] == 0 && blockPtr[5] == 0 && blockPtr[6] == 0 && blockPtr[7] == 0) ) )
        {
            totalSize += 0x10;
        }

        // Check block at offset +40 from blockPtr (absolute offset 0x4C)
        if ( !( (blockPtr[10] == -0x45245246 && blockPtr[11] == -0x41104111 && blockPtr[12] == -0x153ea5ab && blockPtr[13] == -0x6eeff6ef) ||
                (blockPtr[10] == 0 && blockPtr[11] == 0 && blockPtr[12] == 0 && blockPtr[13] == 0) ) )
        {
            totalSize += 0x10;
        }

        blockPtr += 0x18; // Move window by 24 bytes (0x18)
        iterationCount--;
    } while (iterationCount != 0);

    return totalSize;
}