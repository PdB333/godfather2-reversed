// FUNC_NAME: SafeAllocateArray
// Function address: 0x00651a40
// Role: Allocates an array of 4-byte elements with fallback halving on allocation failure.
// Uses a global allocator (DAT_0113d3a4) and throws std::exception on overflow or allocation failure.

void SafeAllocateArray(uint desiredCount, int* outAllocatedPtr, int* outActualCount)
{
    uint count = desiredCount;
    int* allocatedPtr = nullptr;

    // Handle zero or negative (treated as zero) desired count
    if ((int)count < 1) {
        count = 0;
    }
    else {
        // Check for overflow when multiplying by 4 (element size)
        if (0xffffffff / count < 4) {
            // Overflow would occur; throw an exception
            // Standard EA exception throwing pattern
            void* excInfo[2];
            excInfo[0] = 0;
            excInfo[1] = &PTR_LAB_00e31050;  // static exception string table
            if (DAT_0113d3a0 != nullptr) {
                ((void(*)(void**))DAT_0113d3a0)(&excInfo);
            }
            ((void(*)(void))excInfo[2])();
            std::_Throw((exception*)&excInfo);
        }

        // Attempt allocation, halving count on failure
        while (count > 0) {
            allocatedPtr = (int*)FUN_00ba1adf(count * 4, &DAT_0113d3a4);
            if (allocatedPtr != nullptr) {
                break;
            }
            count /= 2;
        }
    }

    // Store results
    *outAllocatedPtr = (int)allocatedPtr;
    *outActualCount = (int)count;
}