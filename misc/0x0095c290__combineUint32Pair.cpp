// FUNC_NAME: combineUint32Pair
uint64 combineUint32Pair(uint32 *lowPtr, uint32 *highPtr)
{
    // Concatenate two 32-bit values into a 64-bit value, high part first
    // Equivalent to CONCAT44(*highPtr, *lowPtr)
    return ((uint64)*highPtr << 32) | *lowPtr;
}